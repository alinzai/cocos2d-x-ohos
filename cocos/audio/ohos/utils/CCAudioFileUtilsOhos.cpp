//
// Created on 2022/11/24.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include <regex>
#include <sys/stat.h>
#include "../audio_utils/AudioFileUtils.h"
#include "../cutils/log.h"
#include <rawfile/raw_file_manager.h>
#include "platform/ohos/napi/modules/RawFileUtils.h"
#include "platform/CCFileUtils.h"


namespace cocos2d { namespace experimental {

AudioFileUtils *AudioFileUtils::sharedFileUtils = nullptr;
NativeResourceManager *AudioFileUtils::_nativeResourceManager = nullptr;

NativeResourceManager *AudioFileUtils::GetRM() {
    if (_nativeResourceManager == nullptr) {
        _nativeResourceManager = RawFileUtils::GetRM();
    }
    return _nativeResourceManager;
}

void AudioFileUtils::setNativeResourceManager(NativeResourceManager *nativeResourceManager) {
    _nativeResourceManager = nativeResourceManager;
}
AudioFileUtils *AudioFileUtils::getInstance() {
    if (sharedFileUtils == nullptr) {
        sharedFileUtils = new AudioFileUtils();
    }
    return sharedFileUtils;
}

void AudioFileUtils::setDelegate(AudioFileUtils *delegate) {
    delete AudioFileUtils::sharedFileUtils;
    AudioFileUtils::sharedFileUtils = delegate;
}

AudioFileUtils::AudioFileUtils() {
    AudioFileUtils::sharedFileUtils = this;
    _searchPathArray.push_back("");
}

AudioFileUtils::~AudioFileUtils() {
    sharedFileUtils = nullptr;
    _nativeResourceManager = nullptr;
}

Data AudioFileUtils::getDataFromFile(const std::string &filename) {
    Data d;
    getContents(filename, &d);
    return d;//FileUtils::getInstance()->getDataFromFile(filename);
}

std::string AudioFileUtils::getSuitableFOpen(const std::string &filenameUtf8) const {
    return filenameUtf8;
}

bool AudioFileUtils::isFileExist(const std::string &filename) const {
    if (isAbsolutePath(filename)) {
        return isFileExistInternal(normalizePath(filename));
    }
    std::string fullpath = fullPathForFilename(filename);
    return !fullpath.empty();
}

AudioFileUtils::Status AudioFileUtils::getContents(const std::string &filename, ResizableBuffer *buffer) {
    if (filename.empty()) {
        return AudioFileUtils::Status::NOT_EXISTS;
    }

    std::string fullPath = fullPathForFilename(filename);
    if (fullPath.empty()) {
        return AudioFileUtils::Status::NOT_EXISTS;
    }

    if (fullPath[0] == '/') {
        return AudioFileUtils::getContents(fullPath, buffer);
    }

    if (nullptr == GetRM()) {
        ALOGE("nativeResourceManager is nullptr");
        return AudioFileUtils::Status::NOT_INITIALIZED;
    }

    RawFile *rawFile = OH_ResourceManager_OpenRawFile(GetRM(), fullPath.c_str());
    if (nullptr == rawFile) {
        return AudioFileUtils::Status::OPEN_FAILED;
    }

    auto size = OH_ResourceManager_GetRawFileSize(rawFile);
    buffer->resize(size);

    assert(buffer->buffer());

    int readsize = OH_ResourceManager_ReadRawFile(rawFile, buffer->buffer(), size);
    // TODO(unknown): read error
    if (readsize < size) {
        if (readsize >= 0) {
            buffer->resize(readsize);
        }
        OH_ResourceManager_CloseRawFile(rawFile);
        return AudioFileUtils::Status::READ_FAILED;
    }
    OH_ResourceManager_CloseRawFile(rawFile);
    return AudioFileUtils::Status::OK;
}

AudioFileUtils::Status AudioFileUtils::getRawFileDescriptor(const std::string &filename, RawFileDescriptor &descriptor) {
    if (filename.empty()) {
        return AudioFileUtils::Status::NOT_EXISTS;
    }

    std::string fullPath = fullPathForFilename(filename);
    if (fullPath.empty()) {
        return AudioFileUtils::Status::NOT_EXISTS;
    }

    if (nullptr == GetRM()) {
        ALOGE("nativeResourceManager is nullptr");
        return AudioFileUtils::Status::NOT_INITIALIZED;
    }

    RawFile *rawFile = OH_ResourceManager_OpenRawFile(GetRM(), fullPath.c_str());
    if (nullptr == rawFile) {
        return AudioFileUtils::Status::OPEN_FAILED;
    }

    bool result = OH_ResourceManager_GetRawFileDescriptor(rawFile, descriptor);
    if (!result) {
        OH_ResourceManager_CloseRawFile(rawFile);
        return AudioFileUtils::Status::OPEN_FAILED;
    }

    OH_ResourceManager_CloseRawFile(rawFile);
    return AudioFileUtils::Status::OK;
}

std::string AudioFileUtils::getFileExtension(const std::string &filePath) const {
    std::string fileExtension;
    size_t pos = filePath.find_last_of('.');
    if (pos != std::string::npos) {
        fileExtension = filePath.substr(pos, filePath.length());

        std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
    }

    return fileExtension;
}

bool AudioFileUtils::isAbsolutePath(const std::string &strPath) const {
    return !strPath.empty() && (strPath[0] == '/');
}

std::string AudioFileUtils::normalizePath(const std::string &path) const {
    std::string ret;
    // Normalize: remove . and ..
    ret = std::regex_replace(path, std::regex("/\\./"), "/");
    ret = std::regex_replace(ret, std::regex("/\\.$"), "");

    size_t pos;
    while ((pos = ret.find("..")) != std::string::npos && pos > 2) {
        size_t prevSlash = ret.rfind('/', pos - 2);
        if (prevSlash == std::string::npos) {
            break;
        }

        ret = ret.replace(prevSlash, pos - prevSlash + 2, "");
    }
    return ret;
}

std::string AudioFileUtils::getPathForFilename(const std::string &filename, const std::string &searchPath) const {
    std::string file{filename};
    std::string filePath;
    size_t pos = filename.find_last_of('/');
    if (pos != std::string::npos) {
        filePath = filename.substr(0, pos + 1);
        file = filename.substr(pos + 1);
    }

    // searchPath + file_path
    std::string path = searchPath;
    path.append(filePath);

    path = getFullPathForDirectoryAndFilename(path, file);

    return path;
}

bool AudioFileUtils::isFileExistInternal(const std::string &strFilePath) const {
    if (strFilePath.empty()) {
        return false;
    }
    std::string strPath = strFilePath;
    if (!isAbsolutePath(strPath)) { // Not absolute path, add the default root path at the beginning.
        strPath.insert(0, _defaultResRootPath);
    }

    if (nullptr == GetRM()) {
        ALOGE("nativeResourceManager is nullptr");
        return false;
    }

    RawFile *rawFile = OH_ResourceManager_OpenRawFile(GetRM(), strPath.c_str());
    if (rawFile) {
        OH_ResourceManager_CloseRawFile(rawFile);
        return true;
    }
    return false;
}

std::string AudioFileUtils::getFullPathForDirectoryAndFilename(const std::string &directory, const std::string &filename) const {
    // get directory+filename, safely adding '/' as necessary
    std::string ret = directory;
    if (!directory.empty() && directory[directory.size() - 1] != '/') {
        ret += '/';
    }
    ret += filename;
    ret = normalizePath(ret);

    // if the file doesn't exist, return an empty string
    if (!isFileExistInternal(ret)) {
        ret = "";
    }
    return ret;
}

std::string AudioFileUtils::fullPathForFilename(const std::string &filename) const {
    if (filename.empty()) {
        return "";
    }

    if (isAbsolutePath(filename)) {
        return normalizePath(filename);
    }

    // Already Cached ?
    auto cacheIter = _fullPathCache.find(filename);
    if (cacheIter != _fullPathCache.end()) {
        return cacheIter->second;
    }

    std::string fullpath;

    for (const auto &searchIt : _searchPathArray) {
        fullpath = this->getPathForFilename(filename, searchIt);

        if (!fullpath.empty()) {
            // Using the filename passed in as key.
            _fullPathCache.emplace(filename, fullpath);
            return fullpath;
        }
    }

    // The file wasn't found, return empty string.
    return "";
}


}} // namespace CocosDenshion