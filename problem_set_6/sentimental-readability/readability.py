# Harvard CS50X Problem Set Submission
# Problem Set 6 - Readability
# By Joshua Lehman - May 7, 2024

def count_letters(text):
    letter_count = 0
    for char in text:
        if char.isalpha():
            letter_count += 1
    return letter_count


def count_words(text):

    if len(text) > 0:
        word_count = 1.00

    for char in text:
        if char == " ":
            word_count += 1.00
    return word_count


def count_sentences(text):
    sentence_count = 0
    for char in text:
        if char in ['.', '!', '?']:
            sentence_count += 1
    return sentence_count


def main():
    text = input("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    L = float((letters/words)*100.0)
    S = float((sentences/words)*100.0)

    index = round((0.0588*L)-(0.296*S)-15.8)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()
