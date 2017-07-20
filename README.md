こんにちは田村柾優紀です。

## 概要
今回公開するのはLookThisWayGame（あっち向いてほいゲーム）です。
このゲームはカメラ映像をもとに顔認識を行い顔の範囲を特定し、その範囲におけるOpticalFlowによりどちらを向いたかを推定し、あっち向いてホイゲームを実現してます。

## 実行環境

実行OS：macOS Sierra 10.12.5

開発環境：XCode Version 8.3.3

使用言語：C,C++

使用ライブラリ：OPENCV3.2

## Xcodeでの実行の仕方

1.Create a new Xcode projectでプロジェクトを作成。

2.macOS->Command Line Toolを選択し、Nextを選択。

3.適当にProject名を記入し、プロジェクトを作成。

4.プロジェクト名のファイルを選択し、BuildSetting->SearchPaths->Header Search PathsにOpenCVのincludeまでのパスを入力（例：/usr/local/Cellar/opencv3/3.2.0/include）し、non-recursiveからrecursiveに変更。

5.次にBuildSettingからBuildPhasesのタブに切り替え、LinkBinaryWithLibrariesにOPENCVのlib内のdylib(例：/usr/local/Cellar/opencv3/3.2.0/libの〜〜〜〜.dylib）を全てドラッグアンドドロップ。

6./usr/local/Cellar/opencv3/3.2.0/share/OpenCV/haarcascadesからhaarcascade_eye_tree_eyeglasses.xmlとhaarcascade_frontalface_alt.xmlを取得。

7./Users/masayuki/Library/Developer/Xcode/DerivedData/LookThisWay-frwmckpoynvsptffarooxqrxgvwo/Build/Products/Debug
に分類器(haarcascade_eye_tree_eyeglasses.xmlとhaarcascade_frontalface_alt.xml)をコピペなどで配置。

8.main.cppをgithub上のmain.cppと置換。

9.実行！
(10.動かなかったらTwitter:@mogamusa31にリプ下さい）

## 参考にさせて頂いたサイト

顔認識：http://docs.opencv.org/3.0-beta/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
OpticalFlow：http://funvision.blogspot.jp/2016/02/opencv-31-tutorial-optical-flow.html