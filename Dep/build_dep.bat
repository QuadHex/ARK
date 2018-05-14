@echo off

echo Building dependencies...

if exist lib (rd lib /q /s)
md lib
cd lib
md Debug
md Release
cd ../

REM If your path is different with below, please change to your install path
set VS150COMNTOOLS=C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\Common7\Tools\
echo "%VS150COMNTOOLS%..\IDE\Devenv"

REM ######################################################################################################
echo Building protobuf...

if exist protobuf (rd protobuf /q /s)
git clone -b 3.5.x https://github.com/google/protobuf.git

cd protobuf/cmake
md build
cd build
cmake -G "Visual Studio 15 Win64" -Dprotobuf_BUILD_SHARED_LIBS=ON -Dprotobuf_BUILD_TESTS=OFF ..
"%VS150COMNTOOLS%..\IDE\Devenv" protobuf.sln /build "Debug|x64"
"%VS150COMNTOOLS%..\IDE\Devenv" protobuf.sln /build "Release|x64"
copy Debug\*.dll ..\..\..\lib\Debug /Y
copy Debug\*.lib ..\..\..\lib\Debug /Y
copy Release\*.dll ..\..\..\lib\Release /Y
copy Release\*.lib ..\..\..\lib\Release /Y

copy Release\libprotobuf.dll ..\..\..\..\Frame\SDK\Proto\proto-gen /Y
copy Release\libprotoc.dll ..\..\..\..\Frame\SDK\Proto\proto-gen /Y
copy Release\protoc.exe ..\..\..\..\Frame\SDK\Proto\proto-gen /Y

cd ..\..\..\

REM ####################################################################################################
echo Building brynet...
if exist brynet (rd brynet /q /s)
git clone -b master https://github.com/ArkGame/brynet.git

cd brynet
md build
cd build
cmake -G "Visual Studio 15 Win64" ..
"%VS150COMNTOOLS%..\IDE\Devenv" brynet.sln /build "Debug|x64" /project brynet.vcxproj
"%VS150COMNTOOLS%..\IDE\Devenv" brynet.sln /build "Release|x64" /project brynet.vcxproj
copy lib\Debug\*.lib ..\..\lib\Debug /Y
copy lib\Release\*.lib ..\..\lib\Release /Y

cd ..\..\
REM ####################################################################################################
REM back to root dir
cd ..\
