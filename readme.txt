USEFUL github commands:
//first right click inside your folder of interest and click "git bash" to open the git command prompt

1) touch filename.hello   // makes a file called filename.hello in the current respository

2)git init   		//makes an empty git repository in the folder

3) git config --global user.name 'Jake Johnson'  	//configure the git repository to appropriate credentials.
   git config --global user.email 'jake.johnson@kuleuven.be' 

4) git add readme.txt //adds readme.txt to the git repository.

5) git status //see what is in the staging area

6)git add . //adds everything to the staging area.
 
7) git commit -m 'whatever comment we want.'

8) In a .gitignore file, add the names of all the files that you want github to ignore when adding to the staging area.

9) git branch branchname //makes a branch called branchname but does not change us to the branch.

10) git checkout branchname //changes the branch from master to branchname 

11) git remote add origin https://github.com/roadjake/coincidence_sort_analyse.git

12) git remote 

13)git push -u origin master