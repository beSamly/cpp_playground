protoc.exe --proto_path=./ --cpp_out=../ *.proto
IF ERRORLEVEL 1 PAUSE