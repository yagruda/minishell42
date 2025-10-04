# An environment variable 
An environment variable is a named value stored by the operating system that programs can use to get information about the system or user preferences.

## 🧠 Think of it like this:
Environment variables are like global settings or system-wide notes that tell programs how to behave.

## 🧩 Examples of Common Environment Variables
| Variable |	Meaning                                                 |
|----------|------------------------------------------------------------|
| PATH     |	List of directories to search for executable programs   |
| HOME     |	Path to the current user's home directory               |
| USER     |	Username of the current user                            |
| PWD      |	Current working directory                               |
| SHELL    |	Default shell (e.g., /bin/bash)                         |
| LANG     |	Language and locale settings                            |


You can check eny env.var in shell:
``` 
echo $PATH 
```

Also in c programm you can get environment from __getenv()__  function