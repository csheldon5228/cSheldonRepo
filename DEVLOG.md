### Entry 1
**Date:** 2026-05-04  
**Entry Type:** Bug Fix   
**Task worked on:** DFS direction selection 
**Issue or decision:** Incorrectly selected a new place to check.  
**Error message / symptom (if applicable):** Continuously ran into errors regarding next selection.  
**What I tried:** Originally did not check for row/column validity. 
**Fix / resolution (or final decision):** Added a check for row/column validity to see if it was a viable option to be explored. 
**Commit(s):** 4,5 