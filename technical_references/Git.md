# Git common syntax

### Configuring

- Setting the name: ```git config --global user.name "<Your name>"```
- Setting the email: ```git config --global user.email "<Your email>"```

### Starting up

1. Initilizing a new repository: ```git init```
2. Creating a remote: ```git remote add <remote shortname> <remote link>```, like ```git remote add origin https://github.com/157239n/NicheFinder.git```
3. Committing: ```git add -A```, ```git commit -m"<Some message>"```, like ```git commit -m"Initial commit"```
4. Pushing up the remote for the first time: ```git push --set-upstream <remote name> <branch name>```

### Routine work

1. Committing: ```git add -A```, ```git commit -m"<Some message>"```
2. Fixing: ```git add -A```, ```git commit --amend -m"<Some new message>"```
3. Pushing: ```git push```

### Git workflow

A typical workflow consist of 2 major branches: master and develop. These run in parallel. Master contains deliverable code and develop contains every other code. So right before you write any code, you should have created identical ```master``` and ```develop``` branches. From now to eternity, you should still have those 2 branches.

#### Actually writing code

1. Checking out develop: ```git checkout develop```
2. Branching to a feature: ```git branch <feature branch name>```, like ```git branch UIBranch```
3. Writing code and committing
4. Checking out develop before merging: ```git checkout develop```
5. Merging our new code in: ```git merge <feature branch name>```, like ```git merge UIBranch```
6. Solving merge conflicts
7. Delete feature branch: ```git branch -d <feature branch name>```, like ```git branch -d UIBranch```

#### Ready to deliver code

1. Checking out develop: ```git checkout develop```
2. Copy develop branch: ```git branch tmpBranch```
3. Checking out master: ```git checkout master```
4. Merge master and the temporary branch: ```git merge tmpBranch```. There should be no merge conflicts, if there are then you're not following the workflow.
5. Delete temporary branch: ```git branch -d tmpBranch```

#### Hotfixes

1. Checking out master: ```git checkout master```
2. Creating hotfix branch: ```git branch hotfix```
3. Fixing the problem encountered
4. Merging with master: ```git checkout master``` and ```git merge hotfix```. There should be no merge conflicts.
5. Merging with develop: ```git checkout develop``` and ```git merge hotfix```
6. Solving merge conflicts
7. Delete hotfix branch: ```git branch -d hotfix```

### More

- Branching from a previous commit: `git branch <branch name> <sha1 of commit>`

[Github's git cheat sheet](https://services.github.com/on-demand/downloads/github-git-cheat-sheet.pdf)
