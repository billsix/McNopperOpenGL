mkdir debugBuild
mkdir debugBuildInstall
cd debugBuild
REM create the visual studio solution and project files
cmake -DCMAKE_INSTALL_PREFIX=..\debugBuildInstall -DCMAKE_BUILD_TYPE=Debug ..\
cmake --build . --target ALL_BUILD --config Debug
cmake --build . --target INSTALL 
cd ..
