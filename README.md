# ETF manager/displayer
Note: This project was created for the course ECE 150 for Project 3. All files except for project_3.cpp and History_Transactions_definitions.hpp were provided for this project.

This program organizes/sorts ETF (exchange-traded funds) transactions and computes various values for each transaction. The transactions are read from the text file transaction_history.txt and are used to calculate values such as adjusted cost base (ACB), adjusted cost base per share (ACB P SHR), and capital gains/losses (CGL).

In addition, the transactions must be sorted chronologically after the text file is initially read. This is extremely important because the order of the transactions directly impact the ACB, ACB per share and CGL.
To do this, an insertion sort is used within the linked list.

Elements/Methods Used:
- Classes
  - Class functions, public/private variables, constructors/destructors
- File Reading
- Pointers and memory management
- Linked lists
- Insertion sort

Disclosure: I do not claim any right, ownership, or the authorship of the other helper files. These files were not coded by me and are solely the property of those who wrote the files (our professors Douglas Harder and Hiren Patel).
