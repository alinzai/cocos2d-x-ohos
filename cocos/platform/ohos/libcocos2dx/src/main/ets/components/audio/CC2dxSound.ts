import CC2dxMusicModel from './CC2dxMusic'

export default class CC2dxSoundPool {
    static soundIdIndex = 0;
    static instance = new CC2dxSoundPool();
    static modelPool = new Map<number, CC2dxMusicModel>();
    static uriPool = new Map<string, number>();
    static volume = 0.5;

    static getInstance() : CC2dxSoundPool {
        return CC2dxSoundPool.instance;
    }

    preload(uri : string) : number {
        var model;
        var soundId;
        if (CC2dxSoundPool.uriPool.has(uri)) {
            soundId = CC2dxSoundPool.uriPool.get(uri);
            model = CC2dxSoundPool.modelPool.get(soundId);
        } else {
            soundId = ++CC2dxSoundPool.soundIdIndex;
            model = new CC2dxMusicModel();
            CC2dxSoundPool.modelPool.set(soundId, model);
            CC2dxSoundPool.uriPool.set(uri, soundId);
        }
        model.preload(uri);
        return soundId;
    }

    play(uri : string, loop) : number{
        if (!CC2dxSoundPool.uriPool.has(uri)) {
            let model;
            let soundId;
            soundId = ++CC2dxSoundPool.soundIdIndex;
            model = new CC2dxMusicModel();
            CC2dxSoundPool.modelPool.set(soundId, model);
            CC2dxSoundPool.uriPool.set(uri, soundId);
            model.setLoop(loop);
            model.preloadAndPlay(uri, true);
            return soundId;
        }
        var soundId = CC2dxSoundPool.uriPool.get(uri);
        var model = CC2dxSoundPool.modelPool.get(soundId);
        model.setLoop(loop);
        model.play(uri, -1, true);
        return soundId;
    }

    stop(soundId : number) {
        if (!CC2dxSoundPool.modelPool.has(soundId)) {
            // TBD 补充日志
            return;
        }
        var model = CC2dxSoundPool.modelPool.get(soundId);
        model.stop();
    }

    stopAll() : number {
        CC2dxSoundPool.uriPool.forEach((soundId:number, key:string, map:Map<string, number>)=>{
            CC2dxSoundPool.getInstance().stop(soundId);
        });
        return 0;
    }

    resume(soundId : number) {
        if (!CC2dxSoundPool.modelPool.has(soundId)) {
            // TBD 补充日志
            return;
        }
        var model = CC2dxSoundPool.modelPool.get(soundId);
        model.resume();
    }

    resumeAll() : number {
        CC2dxSoundPool.uriPool.forEach((soundId:number, key:string, map:Map<string, number>)=>{
            CC2dxSoundPool.getInstance().resume(soundId);
        });
        return 0;
    }

    pause(soundId : number) {
        if (!CC2dxSoundPool.modelPool.has(soundId)) {
            // TBD 补充日志
            return;
        }
        var model = CC2dxSoundPool.modelPool.get(soundId);
        model.pause();
    }

    pauseAll() : number {
        CC2dxSoundPool.uriPool.forEach((soundId:number, key:string, map:Map<string, number>)=>{
            CC2dxSoundPool.getInstance().pause(soundId);
        });
        return 0;
    }

    getVolume() : number {
        return CC2dxSoundPool.volume;
    }

    setVolume(volume) {
        if (volume > 1.0) {
            CC2dxSoundPool.volume = 1.0;
        } else if (volume < 0) {
            CC2dxSoundPool.volume = 0;
        } else {
            CC2dxSoundPool.volume = volume;
        }
        CC2dxSoundPool.modelPool.forEach((model:CC2dxMusicModel, key:number, map:Map<number, CC2dxMusicModel>)=>{
            model.setVolume(CC2dxSoundPool.volume);
        });
    }

    unload(uri) {
        if (!CC2dxSoundPool.uriPool.has(uri)) {
            // TBD 补充日志
            return;
        }
        var soundId = CC2dxSoundPool.uriPool.get(uri);
        var model = CC2dxSoundPool.modelPool.get(soundId);
        model.release();
        CC2dxSoundPool.modelPool.delete(soundId);
        CC2dxSoundPool.uriPool.delete(uri);
    }

    isEffectPreloaded(uri) : boolean {
        return CC2dxSoundPool.uriPool.has(uri);
    }
}