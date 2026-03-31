### Entry 1
**Date:** 2026-03-30  
**Entry Type:** Engineering Decision 
**Task worked on:** Checking Expression Validity  
**Issue or decision:** A universal check should be made first  
**Error message / symptom (if applicable):**   
**What I tried:**  Performing individual checks based on the overarching fix of the expression
**Fix / resolution (or final decision):** Based on the patterns of both infix and postfix expressions, the expression has to follow certain rules such as having an odd number of elements and the parentheses having to be valid  
**Commit(s):** 3,5

---

### Entry 2
**Date:** 2026-03-30  
**Entry Type:** Bug Fix  
**Task worked on:** IsValidInfix  
**Issue or decision:** Checking for infix was messed up due to parentheses possibly existing  
**Error message / symptom (if applicable):** Using ~ instead of ! seemed to mess up the method calles to isValidExpression and isOperator  
**What I tried:** Originally ignored parentheses and thought that using ~ was a correct operation  
**Fix / resolution (or final decision):** Worked around the parentheses by shifting the target for nums vs ops, and made the code clearer by using ! with parentheses around the method calls  
**Commit(s):** 6

---
