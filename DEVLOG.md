### Entry 1
**Date:** 2026-03-07  
**Entry Type:** Bug Fix  
**Task worked on:** Parsing Monopoly Spaces  
**Issue or decision:** Input file stream failed to parse monopoly space data  
**Error message / symptom (if applicable):**  Stuck on first line  
**What I tried:**  Tried to parse the file with the condition as the data parsing  
**Fix / resolution (or final decision):**  Original code actually worked, didn't realize addMany was broken  
**Commit(s):** 6

---

### Entry 2
**Date:** 2026-03-07  
**Entry Type:** Bug Fix  
**Task worked on:** addMany  
**Issue or decision:** addMany function was stuck on the first element 40 times  
**What I tried:** Only focused on the first condition to add each space  
**Fix / resolution (or final decision):** Literally just forgot to increment i  
**Commit(s):** 6

---

