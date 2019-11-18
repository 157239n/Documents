::@echo off
timeout 60
wscript.exe "%~dp0\H.vbs" "%~dp0\deploy.cmd"
git pull
gitpush "Automated git push"