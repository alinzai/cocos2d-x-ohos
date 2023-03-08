import CC2dxMusicModel from './CC2dxMusic'

export default class CC2dxBGMModel {
    private static backgroundMusicModel :  CC2dxMusicModel;
    
    private static instance = new CC2dxBGMModel();
    
    private constructor() {
        CC2dxBGMModel.backgroundMusicModel = new CC2dxMusicModel();
        CC2dxBGMModel.backgroundMusicModel.setLoop(true);
    }

    static getInstance() : CC2dxBGMModel {
        return CC2dxBGMModel.instance;
    }

    preloadBackgroundMusic(uri:string) : number
    {
        return CC2dxBGMModel.backgroundMusicModel.preload(uri);
    }
    
    playBackgroundMusic(uri:string, seek:number, startplay:Boolean, isLoop:Boolean) : number
    {
        CC2dxBGMModel.backgroundMusicModel.setLoop(isLoop);
        return CC2dxBGMModel.backgroundMusicModel.play(uri, seek, startplay);
    }
    
    stopBackgroundMusic() : number
    {
        return CC2dxBGMModel.backgroundMusicModel.stop();
    }

    setBackgroundVolume(volume:number) : number
    {
        return CC2dxBGMModel.backgroundMusicModel.setVolume(volume);
    }
    getBackgroundVolume() : number
    {
        return CC2dxBGMModel.backgroundMusicModel.getVolume();
    }
    
    pauseBackgroundMusic() : number
    {
        return CC2dxBGMModel.backgroundMusicModel.pause();
    }
    
    resumeBackgroundMusic() : number
    {
        return CC2dxBGMModel.backgroundMusicModel.resume();
    }
    
    seekBackgroundMusic(seek : number) : number
    {
        return CC2dxBGMModel.backgroundMusicModel.seek(seek);
    }
    
    releaseBackgroundMusic() : number
    {
        CC2dxBGMModel.backgroundMusicModel.release();
        CC2dxBGMModel.backgroundMusicModel = new CC2dxMusicModel();
        return 0;
    }

}
