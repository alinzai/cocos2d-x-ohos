import media from '@ohos.multimedia.media';
import resourceManager from '@ohos.resourceManager';
import fileIo from '@ohos.fileio'

export enum PlayResult{
    failed,
    success
};

export default class CC2dxMusicModel {
    isPlaying = false;
    player:media.AudioPlayer;
    uri:string;
    currentTimeMs:number;
    duration:number;
    volume:number = 0.5;

    constructor() {
        this.player = media.createAudioPlayer();
        this.player.setVolume(0.5);
    }

    preloadAndPlay(fileUri:string, needPlay:boolean) : number {
        this.uri = fileUri;
        if (fileUri.startsWith('/')) {
           fileIo.open(this.uri, (err, fdNumber) => {
               let fdPath = 'fd://'
               let source = fdPath + fdNumber;
               let self = this;
               if (source === this.player.src && this.player.state != 'idle' && this.player.state != 'stopped') {
                   console.info('MusicPlayer[PlayerModel] preLoad finished. src not changed');
                   //                callback();
               } else if (this.player.state === 'idle') {
                   this.player.on('dataLoad', () => {
                       console.info('MusicPlayer[PlayerModel] dataLoad callback, state=' + self.player.state);
                       //                    callback();
                   });
                   console.info('MusicPlayer[PlayerModel] player.src=' + source);
                   this.player.src = source;
               } else {
                   //                this.notifyPlayingStatus(false);
                   //                this.cancelTimer();
                   console.info('MusicPlayer[PlayerModel] player.reset');
                   self.player.reset();
                   console.info('MusicPlayer[PlayerModel] player.reset done, state=' + self.player.state);
                   self.player.on('dataLoad', () => {
                       console.info('MusicPlayer[PlayerModel] dataLoad callback, state=' + self.player.state);
                       //                    callback();
                   });
                   console.info('MusicPlayer[PlayerModel] player.src=' + source);
                   self.player.src = source;
               }
               console.info('MusicPlayer[PlayerModel] preLoad ' + source + ' end');
               if (needPlay) {
                   this.play(fileUri, -1, true);
               }
           });
           return PlayResult.success;
        }

		let mgr = globalThis.abilityContext.resourceManager;
        mgr.getRawFileDescriptor(fileUri).then(value => {
            let rawFile = value;
            let fdPath = 'fd://'
            let source = fdPath + rawFile.fd;
            if (typeof (source) === 'undefined') {
                console.error('MusicPlayer[PlayerModel] preLoad ignored, source=' + source);
                return;
            }
            let self = this;
            if (source === this.player.src && this.player.state != 'idle' && this.player.state != 'stopped') {
                console.info('MusicPlayer[PlayerModel] preLoad finished. src not changed');
            } else if (this.player.state === 'idle') {
                this.player.on('dataLoad', () => {
                    console.info('MusicPlayer[PlayerModel] dataLoad callback, state=' + self.player.state);
                });
                console.info('MusicPlayer[PlayerModel] player.src=' + source);
                this.player.src = source;
            } else {
                console.info('MusicPlayer[PlayerModel] player.reset');
                self.player.reset();
                console.info('MusicPlayer[PlayerModel] player.reset done, state=' + self.player.state);
                self.player.on('dataLoad', () => {
                    console.info('MusicPlayer[PlayerModel] dataLoad callback, state=' + self.player.state);
                });
                console.info('MusicPlayer[PlayerModel] player.src=' + source);
                self.player.src = source;
            }
            console.info('MusicPlayer[PlayerModel] preLoad ' + source + ' end');
            if (needPlay) {
                this.play(fileUri, -1, true);
            }
        }).catch(error => {
            console.log("getRawFileContent promise error is " + error);
        });
        
        return PlayResult.success;
    }
    
    preload(fileUri:string) : number{
        return this.preloadAndPlay(fileUri, false);
    }

    play(uri, seekTo, startPlay) : number{
        if (uri != this.uri) {
            // 沒有預加載的，需要預加載並播放
            return this.preloadAndPlay(uri, true);
        }
        console.info('MusicPlayer[PlayerModel] play seekTo=' + seekTo + ', startPlay=' + startPlay);
        if (startPlay) {
            if (seekTo < 0 && this.currentTimeMs > 0) {
                console.info('MusicPlayer[PlayerModel] pop seekTo=' + this.currentTimeMs);
                seekTo = this.currentTimeMs;
            }
            let self = this;
            this.player.on('play', () => {
                console.log('MusicPlayer[PlayerModel] play() callback entered, player.state=' + self.player.state);
                if (seekTo > 0) {
                    self.seek(seekTo);
                }
            });
            console.info('MusicPlayer[PlayerModel] call player.play');
            this.player.play();
            this.isPlaying = true;
            console.info('MusicPlayer[PlayerModel] player.play called player.state=' + this.player.state);
        } else if (seekTo > 0) {
            this.currentTimeMs = seekTo;
            console.info('MusicPlayer[PlayerModel] stash seekTo=' + this.currentTimeMs);
        }
        return PlayResult.success;
    }
    
    pause() : number {
        if (!this.isPlaying) {
            console.info('MusicPlayer[PlayerModel] pause ignored, isPlaying=' + this.isPlaying);
            return;
        }
        this.isPlaying = false;
        console.info('MusicPlayer[PlayerModel] call player.pause');
        this.player.pause();
        console.info('MusicPlayer[PlayerModel] player.pause called, player.state=' + this.player.state);
        return PlayResult.success;
    }

    resume() : number {
        if (this.isPlaying) {
            console.info('MusicPlayer[PlayerModel] resume ignored, isPlaying=' + this.isPlaying);
            return;
        }
        this.isPlaying = true;
        console.info('MusicPlayer[PlayerModel] call player.play');
        this.player.play();
        console.info('MusicPlayer[PlayerModel] player.pause called, player.state=' + this.player.state);
        return PlayResult.success;
    }

    seek(ms) : number{
        this.currentTimeMs = ms;
        this.player.seek(ms);
        return PlayResult.success;
    }

    stop() : number{
        if (!this.isPlaying) {
            console.info('MusicPlayer[PlayerModel] stop ignored, isPlaying=' + this.isPlaying);
            return;
        }
        console.info('MusicPlayer[PlayerModel] call player.stop');
        this.player.stop();
        console.info('MusicPlayer[PlayerModel] player.stop called, player.state=' + this.player.state);
        this.isPlaying = false;
        this.uri="";
        return PlayResult.success;
    }

    setVolume(volume:number) : number{
        if (volume > 1.0) {
            this.volume = 1.0;
        } else if (volume < 0) {
            this.volume = 0;
        } else {
            this.volume = volume;
        }
        this.player.setVolume(this.volume);
        return PlayResult.success;
    }

    getVolume() : number{
        return this.volume;
    }

    release() {
        if (typeof (this.player) != 'undefined') {
            console.info('MusicPlayer[PlayerModel] player.release begin');
            this.player.release();
            console.info('MusicPlayer[PlayerModel] player.release end');
            this.player = undefined;
        }
    }

    setLoop(isLoop) {
        this.player.loop = isLoop;
    }
}