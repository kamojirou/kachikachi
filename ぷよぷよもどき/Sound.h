#pragma once

//サウンドシステムを初期化する関数
void StartupSoundSystem();
//サウンドシステムを終了する関数
void ShutdownSoundSystem();

// 指定されたサウンドファイルを開き、再生可能な状態にします。
// 第1引数 path : 
// 戻り値 : サウンドの識別番号
unsigned short OpenSound(const char * path);

// 指定されたサウンドファイルを再生します。
// 第1引数 soundID : 再生したいサウンドの識別番号
void PlaySound2(unsigned short soundID, int loopTimes = 1, bool autoClose = false);

// 指定されたサウンドファイルを停止します。
// 第1引数 soundID : 停止したいサウンドの識別番号
void StopSound(unsigned short soundID);

// 指定されたサウンドファイルを閉じます。
// 第1引数 soundID : 閉じたいサウンドの識別番号
void CloseSound(unsigned short soundID);


