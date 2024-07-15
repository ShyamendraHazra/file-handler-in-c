![file-handler-in-c](https://socialify.git.ci/ShyamendraHazra/file-handler-in-c/image?description=1&font=KoHo&language=1&name=1&pattern=Circuit%20Board&theme=Auto)


# This is a simple repo to just master File Handling in C. 
## To properley and safely interact with text files while also safely managing allocated resources like file streams and heap memory.




### Current Capabilitie of the project

1. #### can open any file in read-write mode and handle possible errors like failed attempts.
2. #### manages a dynamic buffer of max safe length of 65535 characters.
3. #### gracefully handles the errors.

### Current cons or problems

1. #### Doesn't handle the case in case where file size is greater than max safe buffer length.
2. #### Cannot read files bigger than max safe buffer lenght.
3. #### Only has file reading feature.

### Future plans

1. #### [] Add buffer limit check
2. #### [] Add file creation feature
3. #### [] Add text appending feature
