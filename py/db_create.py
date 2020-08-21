import sqlite3
import os


def main():
    os.remove("../test.db")

    conn = sqlite3.connect("../test.db")
    c = conn.cursor()

    c.execute("CREATE TABLE musicinfo (id INTEGER PRIMARY KEY AUTOINCREMENT, fileName TEXT)")
    c.execute("CREATE TABLE hashtable (id INTEGER, hash BLOB, time INTEGER)")
    c.execute("CREATE TABLE record (hash_r BLOB, start INTEGER)")

    conn.commit()
    conn.close()


if __name__ == '__main__':
    main()
