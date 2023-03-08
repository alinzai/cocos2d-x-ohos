/****************************************************************************
 Copyright (c) 2017-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#pragma once
#include <rawfile/raw_file.h>
#include <rawfile/raw_file_manager.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <type_traits>
#include "../CCData.h"
#include "../Macros.h"
#include "../Value.h"
#include "CCPlatformMacros.h"


namespace cocos2d { namespace experimental {

class ResizableBuffer {
  public:
    ~ResizableBuffer() = default;
    virtual void resize(size_t size) = 0;
    virtual void *buffer() const = 0;
};

template <typename T>
class ResizableBufferAdapter {};

template <typename CharT, typename Traits, typename Allocator>
class ResizableBufferAdapter<std::basic_string<CharT, Traits, Allocator>> : public ResizableBuffer {
    using BufferType = std::basic_string<CharT, Traits, Allocator>;
    BufferType *_buffer;

  public:
    explicit ResizableBufferAdapter(BufferType *buffer) : _buffer(buffer) {}
    void resize(size_t size) override {
        _buffer->resize((size + sizeof(CharT) - 1) / sizeof(CharT));
    }
    void *buffer() const override {
        // can not invoke string::front() if it is empty
        return _buffer->empty() ? nullptr : &_buffer->front();
    }
};

template <typename T>
class ResizableBufferAdapter<std::vector<T>> : public ResizableBuffer {
    using BufferType = std::vector<T>;
    BufferType *_buffer;

  public:
    explicit ResizableBufferAdapter(BufferType *buffer) : _buffer(buffer) {}
    void resize(size_t size) override {
        _buffer->resize((size + sizeof(T) - 1) / sizeof(T));
    }
    void *buffer() const override {
        // can not invoke vector::front() if it is empty
        return _buffer->empty() ? nullptr : &_buffer->front();
    }
};

template <>
class ResizableBufferAdapter<Data> : public ResizableBuffer {
    using BufferType = Data;
    BufferType *_buffer;

  public:
    explicit ResizableBufferAdapter(BufferType *buffer) : _buffer(buffer) {}
    void resize(size_t size) override {
        size_t oldSize = _buffer->getSize();
        if (oldSize != size) {
            // need to take buffer ownership for outer memory control
            auto *old = _buffer->takeBuffer(nullptr);
            void *buffer = realloc(old, size);
            if (buffer) {
                _buffer->fastSet(static_cast<unsigned char *>(buffer), static_cast<uint32_t>(size));
            }
        }
    }
    void *buffer() const override {
        return _buffer->getBytes();
    }
};

/** Helper class to handle file operations. */
class AudioFileUtils {
  public:
    /**
     *  Gets the instance of AudioFileUtils.
     */
    static AudioFileUtils *getInstance();

    /**
     *  Destroys the instance of AudioFileUtils.
     */
    CC_DEPRECATED(3.6.0)
    static void destroyInstance();

    /**
     * You can inherit from platform dependent implementation of AudioFileUtils, such as FileUtilsAndroid,
     * and use this function to set delegate, then AudioFileUtils will invoke delegate's implementation.
     * For example, your resources are encrypted, so you need to decrypt it after reading data from
     * resources, then you can implement all getXXX functions, and engine will invoke your own getXX
     * functions when reading data of resources.
     *
     * If you don't want to system default implementation after setting delegate, you can just pass nullptr
     * to this function.
     *
     * @warning It will delete previous delegate
     */
    static void setDelegate(AudioFileUtils *delegate);

    static void setRawFileDescriptor(RawFileDescriptor descriptor);

    /**
     *  Purges full path caches.
     */
    //    virtual void purgeCachedEntries();

    /**
     *  Creates binary data from a file.
     *  @return A data object.
     */
    virtual Data getDataFromFile(const std::string &filename);

    enum class Status {
        OK = 0,
        NOT_EXISTS = 1,        // File not exists
        OPEN_FAILED = 2,       // Open file failed.
        READ_FAILED = 3,       // Read failed
        NOT_INITIALIZED = 4,   // AudioFileUtils is not initializes
        TOO_LARGE = 5,         // The file is too large (great than 2^32-1)
        OBTAIN_SIZE_FAILED = 6 // Failed to obtain the file size.
    };

    /**
     *  Gets whole file contents as string from a file.
     *
     *  Unlike getStringFromFile, these getContents methods:
     *      - read file in binary mode (does not convert CRLF to LF).
     *      - does not truncate the string when '\0' is found (returned string of getContents may have '\0' in the middle.).
     *
     *  The template version of can accept cc::Data, std::basic_string and std::vector.
     *
     *  @code
     *  std::string sbuf;
     *  AudioFileUtils::getInstance()->getContents("path/to/file", &sbuf);
     *
     *  std::vector<int> vbuf;
     *  AudioFileUtils::getInstance()->getContents("path/to/file", &vbuf);
     *
     *  Data dbuf;
     *  AudioFileUtils::getInstance()->getContents("path/to/file", &dbuf);
     *  @endcode
     *
     *  Note: if you read to std::vector<T> and std::basic_string<T> where T is not 8 bit type,
     *  you may get 0 ~ sizeof(T)-1 bytes padding.
     *
     *  - To write a new buffer class works with getContents, just extend ResizableBuffer.
     *  - To write a adapter for existing class, write a specialized ResizableBufferAdapter for that class, see follow code.
     *
     *  @code
     *  namespace cc { // ResizableBufferAdapter needed in cocos2d namespace.
     *  template<>
     *  class ResizableBufferAdapter<AlreadyExistsBuffer> : public ResizableBuffer {
     *  public:
     *      ResizableBufferAdapter(AlreadyExistsBuffer* buffer)  {
     *          // your code here
     *      }
     *      virtual void resize(size_t size) override  {
     *          // your code here
     *      }
     *      virtual void* buffer() const override {
     *          // your code here
     *      }
     *  };
     *  }
     *  @endcode
     *
     *  @param[in]  filename The resource file name which contains the path.
     *  @param[out] buffer The buffer where the file contents are store to.
     *  @return Returns:
     *      - Status::OK when there is no error, the buffer is filled with the contents of file.
     *      - Status::NotExists when file not exists, the buffer will not changed.
     *      - Status::OpenFailed when cannot open file, the buffer will not changed.
     *      - Status::ReadFailed when read end up before read whole, the buffer will fill with already read bytes.
     *      - Status::NotInitialized when AudioFileUtils is not initializes, the buffer will not changed.
     *      - Status::TooLarge when there file to be read is too large (> 2^32-1), the buffer will not changed.
     *      - Status::ObtainSizeFailed when failed to obtain the file size, the buffer will not changed.
     */
    template <
        typename T,
        typename Enable = typename std::enable_if<
            std::is_base_of<ResizableBuffer, ResizableBufferAdapter<T>>::value>::type>
    Status getContents(const std::string &filename, T *buffer) {
        ResizableBufferAdapter<T> buf(buffer);
        return getContents(filename, &buf);
    }
    virtual Status getContents(const std::string &filename, ResizableBuffer *buffer);

    /** Returns the fullpath for a given filename.

     First it will try to get a new filename from the "filenameLookup" dictionary.
     If a new filename can't be found on the dictionary, it will use the original filename.
     Then it will try to obtain the full path of the filename using the AudioFileUtils search rules: resolutions, and search paths.
     The file search is based on the array element order of search paths and resolution directories.

     For instance:

         We set two elements("/mnt/sdcard/", "internal_dir/") to search paths vector by setSearchPaths,
         and set three elements("resources-ipadhd/", "resources-ipad/", "resources-iphonehd")
         to resolutions vector by setSearchResolutionsOrder. The "internal_dir" is relative to "Resources/".

        If we have a file named 'sprite.png', the mapping in fileLookup dictionary contains `key: sprite.png -> value: sprite.pvr.gz`.
         Firstly, it will replace 'sprite.png' with 'sprite.pvr.gz', then searching the file sprite.pvr.gz as follows:

             /mnt/sdcard/resources-ipadhd/sprite.pvr.gz      (if not found, search next)
             /mnt/sdcard/resources-ipad/sprite.pvr.gz        (if not found, search next)
             /mnt/sdcard/resources-iphonehd/sprite.pvr.gz    (if not found, search next)
             /mnt/sdcard/sprite.pvr.gz                       (if not found, search next)
             internal_dir/resources-ipadhd/sprite.pvr.gz     (if not found, search next)
             internal_dir/resources-ipad/sprite.pvr.gz       (if not found, search next)
             internal_dir/resources-iphonehd/sprite.pvr.gz   (if not found, search next)
             internal_dir/sprite.pvr.gz                      (if not found, return "sprite.png")

        If the filename contains relative path like "gamescene/uilayer/sprite.png",
        and the mapping in fileLookup dictionary contains `key: gamescene/uilayer/sprite.png -> value: gamescene/uilayer/sprite.pvr.gz`.
        The file search order will be:

             /mnt/sdcard/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz      (if not found, search next)
             /mnt/sdcard/gamescene/uilayer/resources-ipad/sprite.pvr.gz        (if not found, search next)
             /mnt/sdcard/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz    (if not found, search next)
             /mnt/sdcard/gamescene/uilayer/sprite.pvr.gz                       (if not found, search next)
             internal_dir/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz     (if not found, search next)
             internal_dir/gamescene/uilayer/resources-ipad/sprite.pvr.gz       (if not found, search next)
             internal_dir/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz   (if not found, search next)
             internal_dir/gamescene/uilayer/sprite.pvr.gz                      (if not found, return "gamescene/uilayer/sprite.png")

     If the new file can't be found on the file system, it will return the parameter filename directly.

     This method was added to simplify multiplatform support. Whether you are using cocos2d-js or any cross-compilation toolchain like StellaSDK or Apportable,
     you might need to load different resources for a given file in the different platforms.

     @since v2.1
     */
    virtual std::string fullPathForFilename(const std::string &filename) const;

    /**
     *  Sets the array of search paths.
     *
     *  You can use this array to modify the search path of the resources.
     *  If you want to use "themes" or search resources in the "cache", you can do it easily by adding new entries in this array.
     *
     *  @note This method could access relative path and absolute path.
     *        If the relative path was passed to the vector, AudioFileUtils will add the default resource directory before the relative path.
     *        For instance:
     *            On Android, the default resource root path is "@assets/".
     *            If "/mnt/sdcard/" and "resources-large" were set to the search paths vector,
     *            "resources-large" will be converted to "@assets/resources-large" since it was a relative path.
     *
     *  @param searchPaths The array contains search paths.
     *  @see fullPathForFilename(const char*)
     *  @since v2.1
     */
    //    virtual void setSearchPaths(const std::vector<std::string> &searchPaths);

    /**
     * Get default resource root path.
     */
    const std::string &getDefaultResourceRootPath() const;

    /**
     * Set default resource root path.
     */
    void setDefaultResourceRootPath(const std::string &path);

    /**
     * Windows fopen can't support UTF-8 filename
     * Need convert all parameters fopen and other 3rd-party libs
     *
     * @param filenameUtf8 std::string name file for conversion from utf-8
     * @return std::string ansi filename in current locale
     */
    virtual std::string getSuitableFOpen(const std::string &filenameUtf8) const;

    /**
     *  Checks whether a file exists.
     *
     *  @note If a relative path was passed in, it will be inserted a default root path at the beginning.
     *  @param filename The path of the file, it could be a relative or absolute path.
     *  @return True if the file exists, false if not.
     */
    virtual bool isFileExist(const std::string &filename) const;

    /**
     *  Gets filename extension is a suffix (separated from the base filename by a dot) in lower case.
     *  Examples of filename extensions are .png, .jpeg, .exe, .dmg and .txt.
     *  @param filePath The path of the file, it could be a relative or absolute path.
     *  @return suffix for filename in lower case or empty if a dot not found.
     */
    virtual std::string getFileExtension(const std::string &filePath) const;

    /**
     *  Checks whether the path is an absolute path.
     *
     *  @note On Android, if the parameter passed in is relative to "@assets/", this method will treat it as an absolute path.
     *        Also on Blackberry, path starts with "app/native/Resources/" is treated as an absolute path.
     *
     *  @param path The path that needs to be checked.
     *  @return True if it's an absolute path, false if not.
     */
    virtual bool isAbsolutePath(const std::string &path) const;

    /** Returns the full path cache. */
    const std::unordered_map<std::string, std::string> &getFullPathCache() const { return _fullPathCache; }

    virtual std::string normalizePath(const std::string &path) const;

    Status getRawFileDescriptor(const std::string &filename, RawFileDescriptor &descriptor);

    static void setNativeResourceManager(NativeResourceManager *nativeResourceManager);

  protected:
    /**
     *  Checks whether a file exists without considering search paths and resolution orders.
     *  @param filename The file (with absolute path) to look up for
     *  @return Returns true if the file found at the given absolute path, otherwise returns false
     */
    bool isFileExistInternal(const std::string &filename) const;

    /**
     *  Gets full path for filename, resolution directory and search path.
     *
     *  @param filename The file name.
     *  @param searchPath The search path.
     *  @return The full path of the file. It will return an empty string if the full path of the file doesn't exist.
     */
    virtual std::string getPathForFilename(const std::string &filename, const std::string &searchPath) const;

    /**
     *  Gets full path for the directory and the filename.
     *
     *  @note Only iOS and Mac need to override this method since they are using
     *        `[[NSBundle mainBundle] pathForResource: ofType: inDirectory:]` to make a full path.
     *        Other platforms will use the default implementation of this method.
     *  @param directory The directory contains the file we are looking for.
     *  @param filename  The name of the file.
     *  @return The full path of the file, if the file can't be found, it will return an empty string.
     */
    virtual std::string getFullPathForDirectoryAndFilename(const std::string &directory, const std::string &filename) const;

    /**
     * The vector contains search paths.
     * The lower index of the element in this vector, the higher priority for this search path.
     */
    std::vector<std::string> _searchPathArray;

    /**
     * The search paths which was set by 'setSearchPaths' / 'addSearchPath'.
     */
    std::vector<std::string> _originalSearchPaths;

    /**
     *  The default root path of resources.
     *  If the default root path of resources needs to be changed, do it in the `init` method of AudioFileUtils's subclass.
     *  For instance:
     *  On Android, the default root path of resources will be assigned with "@assets/" in FileUtilsAndroid::init().
     *  Similarly on Blackberry, we assign "app/native/Resources/" to this variable in FileUtilsBlackberry::init().
     */
    std::string _defaultResRootPath;

    /**
     *  The full path cache. When a file is found, it will be added into this cache.
     *  This variable is used for improving the performance of file search.
     */
    mutable std::unordered_map<std::string, std::string> _fullPathCache;

    /**
     * Writable path.
     */
    std::string _writablePath;

    /**
     *  The singleton pointer of AudioFileUtils.
     */
    static AudioFileUtils *sharedFileUtils;

    static NativeResourceManager *_nativeResourceManager;

  private:
    /**
     *  The default constructor.
     */
    AudioFileUtils();

    /**
     *  The destructor of AudioFileUtils.
     */
    virtual ~AudioFileUtils();

    static NativeResourceManager *GetRM();
};

}} // namespace CocosDenshion
