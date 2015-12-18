ArgumentParser
==============

A small, simple utility for parsing whitespace-separated arguments.

This library is meant to help in writing interactive command-line programs that use command-line-style arguments. 

For example:

=> create-user --username bob --password "5om3 53cr3t p4a55w0rd" 

Arguments are separated by whitespace.
Arguments can be optionally surrounded by single or double quotes.
Singly- or doubly- quoted arguments can include single and double quotes (respectively) by escaping them with a backslash.

