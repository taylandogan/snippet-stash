# -*- coding: utf-8 -*-
import re
import sys
import os
from os import listdir
from os.path import isfile, join
import nltk.data
from nltk.tokenize import sent_tokenize
import ebooklib
from ebooklib import epub
from sets import Set
from bs4 import BeautifulSoup
from HTMLParser import HTMLParser



# Removes headers, spans and links
def preprocess_html(raw_html):
    headers = re.compile(r"(<h1.*?/h1>)|(<span.*?>)|(</span>)|(<a.*?/>)|(<a.*?</a>)")
    preprocessed = re.sub(headers, "", raw_html)
    return preprocessed


# Removes newlines, tabs, carriage returns and things in curly braces
def custom_strip(text):
    unwanted_chars = re.compile(r"(\n)|(\t)|(\r)|({.*?})")
    text = re.sub(unwanted_chars, "", text)
    return text


# After getting paragraphs, clean them with this method
def process_paragraph(p):
    '''
    replacements = {
        '“': '',
        '”': '',
        '"': '',
        '’': "'",
        '‘': "'",
        '…': '...',
        '—': '-',
        'â': 'a',
        'Â': 'A',
        'û': 'u'
    }

    p = "".join([replacements.get(c, c) for c in p])
    '''
    p = re.sub('“', '', p)
    p = re.sub('”', '', p)
    return p


def print_non_ascii_chars(p):
    p = list(re.sub('[ -~]', '', p, flags=re.U))
    s = Set(p)
    s = repr([x.encode(sys.stdout.encoding) for x in s]).decode('string-escape')
    print s


def read(filepath):
    ebook = epub.read_epub(filepath)

    # We're interested in document items in the ebook
    all_paragraphs = []
    for item in ebook.get_items_of_type(ebooklib.ITEM_DOCUMENT):
        text = item.get_content()
        text = preprocess_html(text)
        soup = BeautifulSoup(text, 'html.parser')
        paragraphs = soup.find_all('p')
        all_paragraphs.extend(paragraphs)

    for i in xrange(len(all_paragraphs)):
        p = all_paragraphs[i]
        p = p.text
        p = p.encode('utf-8')
        p = process_paragraph(p)
        all_paragraphs[i] = p

    content = '\n'.join(str(p) for p in all_paragraphs)
    return content


def load_nltk_sentence_detector():
    return nltk.data.load('tokenizers/punkt/turkish.pickle')


# Takes a text, returns a sentence list
def tokenize_sentences(text, sentence_detector):
    return sentence_detector.tokenize(text.strip())


# Processes each epub in the given folder path, then puts results to output_path
def process_path(epub_path, output_path):
    sentence_detector = load_nltk_sentence_detector()
    files_in_path = [f for f in listdir(epub_path) if isfile(join(epub_path, f))]
    could_not_parse = []
    for f in files_in_path:
        try:
            ext = os.path.splitext(f)[-1].lower()
            if ext == ".epub":
                file_path = epub_path + '/' + f
                filename = os.path.basename(f)
                output_file = output_path + '/' + filename + '.txt'
                content = read(file_path)
                #print 'Path:', file_path
                print 'Filename:' , filename
                #print 'Output file:', output_file

                all_sentences = []
                for line in content.splitlines():
                    sentences = tokenize_sentences(line.decode("utf-8"), sentence_detector)
                    all_sentences.extend(sentences)

                content = '\n'.join(s.encode("utf-8") for s in all_sentences)

                with open(output_file, mode="w") as out:
                    out.write(content)
        except Exception, e:
            could_not_parse.append(f)
    print "Could not parse the files: ", "\n".join(could_not_parse)

if __name__ == '__main__':
    epub_path = "/home/taylan/local/NLP/turkish_book_collection/t/Türkçe [ePub]/Derecelendirilmiş Kitaplar"
    #epub_path = "/home/taylan/w_Python/skip_thoughts/resources/epub"
    output_path = "/home/taylan/w_Python/skip_thoughts/resources/text"
    process_path(epub_path, output_path)
