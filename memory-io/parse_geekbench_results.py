"""
Geekbench uploads benchmark results to a unique web page.
This script extracts parses memory scores from these web pages.
The links to the pages is provided via stdin to given script.

Example <stdin>:

http://browser.primatelabs.com/geekbench3/5047761
http://browser.primatelabs.com/geekbench3/5047805
http://browser.primatelabs.com/geekbench3/5047807
http://browser.primatelabs.com/geekbench3/5047881
http://browser.primatelabs.com/geekbench3/5047882
http://browser.primatelabs.com/geekbench3/5047886
http://browser.primatelabs.com/geekbench3/5047875
[EOF = Ctrl + D]
"""
import sys,urllib2
from bs4 import BeautifulSoup

def scrape(url):
    content = urllib2.urlopen(url).read()
    soup = BeautifulSoup(content)

    section_table = soup.findAll("table", { "class" : "table table-striped geekbench2-show section-performance" })

    # Memory scores
    print str(section_table[2].findAll('th')[1].contents[0]) + '\t',
    print str(section_table[2].findAll('th')[4].contents[0]),

    # Memory Details
    #for i in range(1, 23, 3):
    #    print section_table[2].findAll('td')[i].contents[5].text



lines = sys.stdin.readlines()
print "Memory (Single Core)" + '\t',
print "Memory (Multi Core)" + '\t'
for l in lines:
    try:
        link = l[:-1]
        scrape(link)
    pass:
        # Ignore blank lines if any
    print