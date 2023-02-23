# emails.c
Given a list of email addresses in "full name &lt;email address>" format, print only the email addresses, with each of the email addresses on its own line.

Uses libICU for Unicode support. You will need to install the appropriate libraries & header files using your distribution's package facilities or by other means.

Example build:

    cc -o emails emails.c -licuio

Usage example:

    # Results will be in "email-list-out.txt"
    ./emails <email-list.txt >email-list-out.txt
