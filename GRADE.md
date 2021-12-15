# Final Project : cs253-f21-final-exam  

---

## Grading Summary  
Name: ERICMELIN  
Date: Wed Dec 15 05:30:29 2021 -0700  
Grade: 120/120  
Comment: Excellent Work!  

---

## Final Project  
### Code Style (20/20)  
**Criteria:**  Code style is consistent with the specified Style Guide  

- Manual review completed successfully

### Code Quality (20/20)  
**Criteria:**  Code compiles without warnings runs without warnings or errors and is free of memory errors and leaks.  
```
- Quality Test - Clean Build Check: passed 
- Quality Test - Run Check (myps): passed 
- Quality Test - Memory Check (myps): passed 
```
### Unit Testing (40/40)  
**Criteria:**  Functions implemented in ProcEntry.c follow the described behavior documented in the ProcEntry.h header file. Unit tests must run without memory errors to pass.  
```
- Unit Test - Create/Destroy ProcEntry: passed 
- Unit Test - CreateFromFile (onyx_proc/9906/stat): passed 
- Unit Test - CreateFromFile (NULL): passed 
- Unit Test - CreateFromFile (Does Not Exist): passed 
- Unit Test - CreateFromFile (Invalid Format): passed 
- Unit Test - PrintProcEntry (onyx_proc/9906/stat): passed 
- Unit Test - PrintProcEntry (onyx_proc/19070/stat): passed 
- Unit Test - PrintProcEntry (onyx_proc/593/stat): passed 
- Unit Test - PrintProcEntry (onyx_proc/1/stat): passed 
- Unit Test - PrintProcEntry (budgie_proc/55986/stat): passed 
```
### Integration Testing (40/40)  
**Criteria:**  Solution fully satisfies all requirements specified in the Project Guide and produces the expected output.  
```
- Integration Test - Looking for bash (/proc): passed 
- Integration Test - Looking for systemd (/proc): passed 
- Integration Test - Looking for NetworkManager (/proc): passed 
- Integration Test - PID Sort (onyx_proc): passed 
- Integration Test - PID Sort (budgie_proc): passed 
- Integration Test - CMD Sort (onyx_proc): passed 
- Integration Test - CMD Sort (budgie_proc): passed 
- Integration Test - Zombies Only (onyx_proc): passed 
- Integration Test - Zombies Only (budgie_proc): passed 
- Integration Test - Usage / Help: passed 
```
### Extra Credit (0/25)  
**Criteria:**  Solution fully satisfies all requirements specified in the Project Guide and produces the expected output.  
```
    - Extra Credit - Single Space Test: failed (nonzero exit status) 
    - Extra Credit - Two Spaces Test: failed (nonzero exit status) 
    - Extra Credit - Many Spaces Test: failed (nonzero exit status) 
    - Extra Credit - Nested Parans Test: failed (nonzero exit status) 
    - Extra Credit - Surrounded Words Test: failed (nonzero exit status) 
```
