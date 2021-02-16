#!/bin/bash

cd ~/logs
git pull
git add -A
git commit -m"Automated git push"
git push origin master
