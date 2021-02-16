#!/bin/bash

cd ~/logs
echo "Inside autopush"
git pull
git add -A
git commit -m"Automated git push"
git push origin master
