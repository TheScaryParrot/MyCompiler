import sys
import os

ALIAS_COMMENT_ENTER = ['/*', '#enterComment']
ALIAS_COMMENT_EXIT = ['*/', '#exitComment']

ALIAS_LITERAL_CODE = ['"']

ALIASES = {
    '[': '#enterOrderQueue',
    ']': '#exitOrderQueue',
    '>>': '#assign',
    '->': '#assignToOne',
    '\\n': '"\n"',
    ';': '"\n" #clearOrderQueue',
    '!': '#force',
    '?!': '#lightForce',
}

WHITESPACES = [' ', '\t', '\n']


def isWhitespace(char: str) -> bool:
    return char in WHITESPACES


class Fetcher:
    def __init__(self, file):
        self.file = file

    def nextToken(self) -> str:
        # remove all whitespace
        self.removeUselessStuff()

        # read until the next whitespace
        token = ''
        while True:
            char = self.file.read(1)
            if not char or isWhitespace(char):
                return token
            token += char

    def removeUselessStuff(self):
        while True:
            if self.removeWhitespaces():
                continue

            for commentEnter in ALIAS_COMMENT_ENTER:
                if self.isNext(commentEnter):
                    self.consumeComment()
                    continue

            return

    def removeWhitespaces(self) -> bool:
        # returns whether a whitespace was removed
        anyRemoved = False

        while True:
            for whitespace in WHITESPACES:
                if self.isNext(whitespace):
                    self.file.read(1)
                    anyRemoved = True
                    continue

            return anyRemoved

    def isNext(self, string: str) -> bool:
        # returns true and consumes the string if the next characters in the file are the same as the string
        pos = self.file.tell()
        for char in string:
            if char != self.file.read(1):
                self.file.seek(pos)
                return False
        return True

    def consumeLiteral(self) -> str:
        # consumes until a ALIAS_LITERAL_CODE is reached
        while True:
            for literalExit in ALIAS_LITERAL_CODE:
                if self.isNext(literalExit):
                    return
            self.file.read(1)

    def consumeComment(self):
        # consumes until a ALIAS_COMMENT_EXIT is reached
        while True:
            for commentExit in ALIAS_COMMENT_EXIT:
                if self.isNext(commentExit):
                    return
            self.file.read(1)

    def isDone(self) -> bool:
        # check whether the file has reached end of file
        return self.file.tell() == os.fstat(self.file.fileno()).st_size


def dealias(string: str):
    for alias, value in ALIASES.items():
        if string == alias:
            return value

    return string


if __name__ == '__main__':
    filename = sys.argv[1]
    outFileName = sys.argv[2]

    outstring: str = ''

    with open(filename, 'r') as inFile:
        fetcher = Fetcher(inFile)
        while not fetcher.isDone():
            outstring += dealias(fetcher.nextToken()) + "\n"

    with open(outFileName, 'w') as outFile:
        outFile.write(outstring)
