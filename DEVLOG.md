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

### Entry 3
**Date:** 2026-03-31  
**Entry Type:** Bug Fix  
**Task worked on:** ArrayStack.pop() & ArrayStack.push()  
**Issue or decision:**  vector.append() and vector.erase() do not exist, or were being misused  
**Error message / symptom (if applicable):** error: no matching function for call to 'std::vector<Token>::erase(__gnu_cxx::__alloc_traits<std::allocator<Token>, Token>::value_type&)'  
**What I tried:** Tried to use those vector functions, thinking they would work  
**Fix / resolution (or final decision):** For push, just had to use vector.push_back() and for the pop, just had to use vector.pop_back()  
**Commit(s):** 8,9

---

### Entry 4
**Date:** 2026-03-31  
**Entry Type:** Bug Fix  
**Task worked on:** infixToPostFix  
**Issue or decision:** Last operator in stack was not being added to the output vector   
**Error message / symptom (if applicable):** Forgot to completely empty stack  
**What I tried:** Originally forgot to fully flush stack  
**Fix / resolution (or final decision):** After full iteration through the input vector, the stack gets flushed to the output vector  
**Commit(s):** 9

---

### Entry 5
**Date:** 2026-03-31  
**Entry Type:** Edge Case  
**Task worked on:** infixToPostFix  
**Issue or decision:** Failure of different precedences to be added correctly, or a closing parens is at the end of the input   
**Error message / symptom (if applicable):** Was getting out of bounds error with the parens glitch   
**What I tried:** Did not account for parens at end of input, and did not have a way to check for the previous operator being of higher precedence than current  
**Fix / resolution (or final decision):** Added statement to initial operator check so that the precedence could be handled correctly, along with fixing the parens issue  
**Commit(s):** 10