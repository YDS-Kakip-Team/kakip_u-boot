# Kakip u-boot


## ビルド環境

[Renesas社の手順](https://renesas-rz.github.io/rzv_ai_sdk/5.00/getting_started.html)を参考にRZ/V2H用AI SDKのコンテナイメージを作成してください。

## ビルド手順

1. 作業ディレクトリの作成

    ```
    mkdir kakip_work
    export WORK=$PWD/kakip_work
    ```

2. リポジトリのクローン

    ```
    cd $WORK
    git clone https://github.com/Kakip-ai/kakip_u-boot
    ```

3. カーネルコンフィグの設定

    ```
    cd $WORK/kakip_u-boot
    cp ./kakip.config .config
    ```

4. arm-trusted-firmwareのクローン

    ```
    cd $WORK
    git clone -b v2.2 https://github.com/ARM-software/arm-trusted-firmware
    ```

3. ビルド環境(コンテナ)の起動

    環境によってはsudoを付けて実行する必要があります。

    ```
    cd $WORK
    docker run --rm -it -v $PWD:/kakip_work -w /kakip_work rzv2h_ai_sdk_image
    ```

4. 環境変数の設定と依存パッケージのインストール

    ```
    source /opt/poky/3.1.31/environment-setup-aarch64-poky-linux
    apt update && apt install -y libssl-dev
    ```

5. u-bootのビルド

    ```
    cd /kakip_work/kakip_u-boot
    make -j4
    ```

6. fiptoolのビルド

    ```
    cd /kakip_work/arm-trusted-firmware/tools/fiptool
    make -j4
    ```

7. Firmware Packageの作成

    ```
    cd /kakip_work/kakip_u-boot
    ../arm-trusted-firmware/tools/fiptool/fiptool create --align 16 --soc-fw bl31-kakip-es1.bin --nt-fw u-boot.bin fip.bin
    ```

    Firmware Packageは以下の通りです。

    - ./fip.bin

    Firmware Packageの作成後はexitでコンテナから抜けて下さい。

    ```
    exit
    ```

## u-bootの更新

Kakipのイメージが書き込まれているSDカードを更新します。

1. SDカードをPCに挿す

    /dev/sd<x>として認識されます。<x>は環境によります。

2. 作成したFirmware PackageをSDカードに書き込む

    ```
    cd $WORK/kakip_u-boot
    sudo dd if=fip.bin of=/dev/sd<x> seek=768 conv=notrunc
    sync
    ```