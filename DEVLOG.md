### Entry 1
**Date:** 2026-03-07  
**Entry Type:** Bug Fix  
**Task worked on:** Parsing Monopoly Spaces  
**Issue or decision:** Input file stream failed to parse monopoly space data  
**Error message / symptom (if applicable):**  Stuck on first line  
**What I tried:**  Tried to parse the file with the condition as the data parsing, also attempted to parse each individual line
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

### Entry 3
**Date:** 2026-03-07  
**Entry Type:** Engineering Decision  
**Task worked on:** MonopolySpaces.csv  
**Issue or decision:** Monopoly spaces vary in name length, often with more than one or two words  
**What I tried:** Parsing each word of the monopoly space csv  
**Fix / resolution (or final decision):** Opted to use a string stream object to split each line by commas  
**Commit(s):** 7

---

### Entry 4
**Date:** 2026-03-08  
**Entry Type:** Testing Entry  
**Task worked on:** findByColor  
**Issue or decision:** Failed in testing due errors in references  
**What I tried:** Accidentally referred to fields that did not exist in the MonopolySpace  
**Fix / resolution (or final decision):** Changed the reference variables to match what was in the MonopolySpaces class  
**Commit(s):** 8

---

### Entry 5
**Date:** 2026-03-08  
**Entry Type:** Engineering Decision  
**Task worked on:** MonopolySpaces.csv  
**Issue or decision:** Every monopoly space saved into csv file  
**What I tried:** Originally kept test spaces in, with GO as a separate function call  
**Fix / resolution (or final decision):** Wrote the data for each space into the csv so that all 40 spaces are stored together & tested edge cases  
**Commit(s):** 8