# emails.c
Given a list of email addresses in "full name &lt;email address>" format, print only the email addresses, with each of the email addresses on its own line.

Uses libICU for Unicode support.

Example build:

    cc -o emails emails.c -licuio
