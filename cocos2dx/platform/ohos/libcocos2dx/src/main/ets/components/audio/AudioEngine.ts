import CC2dxMusicModel from './CC2dxMusic'
import CC2dxSound from './CC2dxSound'


let backgroundMusicModel = new CC2dxMusicModel();
backgroundMusicModel.setLoop(true);
function preloadBackgroundMusic(uri:string) : number
{
    return backgroundMusicModel.preload(uri);
}

function playBackgroundMusic(uri:string, seek:number, startplay:Boolean) : number
{
    return backgroundMusicModel.play(uri, seek, startplay);
}

function stopBackgroundMusic() : number
{
    return backgroundMusicModel.stop();
}
function setBackgroundVolume(volume:number) : number
{
    return backgroundMusicModel.setVolume(volume);
}
function getBackgroundVolume() : number
{
    return backgroundMusicModel.getVolume();
}

function pauseBackgroundMusic() : number
{
    return backgroundMusicModel.pause();
}

function resumeBackgroundMusic() : number
{
    return backgroundMusicModel.resume();
}

function seekBackgroundMusic(seek : number) : number
{
    return backgroundMusicModel.seek(seek);
}

function releaseBackgroundMusic() : number
{
    backgroundMusicModel.release();
    backgroundMusicModel = new CC2dxMusicModel();
    return 0;
}


globalThis.ccCpp2Js={};
globalThis.ccCpp2Js.preloadBackgroundMusic=preloadBackgroundMusic;
globalThis.ccCpp2Js.playBackgroundMusic=playBackgroundMusic;
globalThis.ccCpp2Js.stopBackgroundMusic=stopBackgroundMusic;
globalThis.ccCpp2Js.setBackgroundVolume=setBackgroundVolume;
globalThis.ccCpp2Js.getBackgroundVolume=getBackgroundVolume;
globalThis.ccCpp2Js.pauseBackgroundMusic=pauseBackgroundMusic;
globalThis.ccCpp2Js.resumeBackgroundMusic=resumeBackgroundMusic;
globalThis.ccCpp2Js.seekBackgroundMusic=seekBackgroundMusic;
globalThis.ccCpp2Js.releaseBackgroundMusic=releaseBackgroundMusic;

globalThis.ccCpp2Js.getEffectsVolume=CC2dxSound.getInstance().getVolume;
globalThis.ccCpp2Js.setEffectsVolume=CC2dxSound.getInstance().setVolume;
globalThis.ccCpp2Js.playEffect=CC2dxSound.getInstance().play;
globalThis.ccCpp2Js.pauseEffect=CC2dxSound.getInstance().pause;
globalThis.ccCpp2Js.pauseAllEffects=CC2dxSound.getInstance().pauseAll;
globalThis.ccCpp2Js.resumeEffect=CC2dxSound.getInstance().resume;
globalThis.ccCpp2Js.resumeAllEffects=CC2dxSound.getInstance().resumeAll;
globalThis.ccCpp2Js.stopEffect=CC2dxSound.getInstance().stop;
globalThis.ccCpp2Js.stopAllEffects=CC2dxSound.getInstance().stopAll;
globalThis.ccCpp2Js.preloadEffect=CC2dxSound.getInstance().preload;
globalThis.ccCpp2Js.isEffectPreloaded=CC2dxSound.getInstance().isEffectPreloaded
globalThis.ccCpp2Js.unloadEffect=CC2dxSound.getInstance().unload;


