from __future__ import unicode_literals
import sys
import datetime
import codecs

# heeeheee
env = {"__name__":"__notmain__"}
execfile("caja-dropbox", env)
commands = env["commands"]

with codecs.open("AUTHORS", "r", "utf-8") as afile:
    authors = '| ' + afile.read().replace('\n', '\n| ')

with codecs.open(sys.argv[2], "r", encoding="utf-8") as infile:
    instr = infile.read()

formatted_commands = ""
for cmd in commands:
    split = commands[cmd].__doc__.split('\n', 2)
    formatted_commands += split[1].replace(cmd, "`%s`" % cmd).replace("dropbox", "``dropbox``")
    formatted_commands += split[2].replace('\n', '\n  | ')
    formatted_commands += '\n\n'

replace = {'@AUTHORS@': authors,
           '@DATE@': datetime.date.today().isoformat(),
           '@PACKAGE_VERSION@': sys.argv[1],
           '@SYNOPSIS@':  '| '+'\n| '.join(commands[cmd].__doc__.split('\n', 2)[1].replace(cmd, "`%s`" % cmd).replace("dropbox", "``dropbox``") for cmd in commands),
           '@COMMANDS@': formatted_commands}

for r in replace.keys():
    instr = instr.replace(r, replace[r])

with codecs.open(sys.argv[3], "w", encoding="utf-8") as outfile:
    outfile.write(instr)
