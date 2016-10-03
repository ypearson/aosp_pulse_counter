#!/bin/sh
TOP=../../../../..

${TOP}/development/build/tools/mk_sdk_repo_xml.sh  addon.xml \
${TOP}/prebuilts/devtools/repository/sdk-addon-03.xsd \
add-on linux  \
${TOP}/out/host/linux-x86/sdk_addon/rcnt_library-eng.ypearson-linux-x86.zip

cp addon.xml ${TOP}/out/host/linux-x86/sdk_addon/addon.xml

cd ${TOP}/out/host/linux-x86/sdk_addon/

python -m SimpleHTTPServer 8000
