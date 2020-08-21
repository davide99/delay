import sqlite3
import os


def main():
    os.remove("../test.db")

    conn = sqlite3.connect("../test.db")
    c = conn.cursor()

    c.execute("CREATE TABLE musicinfo (id INTEGER PRIMARY KEY AUTOINCREMENT, fileName TEXT)")
    c.execute("CREATE TABLE hashtable (id INTEGER, hash BLOB, time INTEGER, PRIMARY KEY(id, hash, time))")
    c.execute("CREATE TABLE record (hash_r BLOB, start INTEGER, PRIMARY KEY(hash_r, start))")

    conn.commit()
    conn.close()


if __name__ == '__main__':
    main()
