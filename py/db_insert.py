import sqlite3


def main():
    conn = sqlite3.connect("../test.db")
    c = conn.cursor()

    c.execute("INSERT INTO musicinfo (fileName) VALUES (\"test.wav\");")
    id = c.lastrowid

    sql = "INSERT INTO hashtable (id, hash, time) VALUES "

    lines = []

    with open("../links.txt") as f:
        for line in f:
            lines.append(line.strip())

    lines = list(set(lines))

    links = []
    for line in lines:
        links.append(line.split(";"))

    for link in links:
        sql += "(" + str(id) + "," + str(link[0]) + "," + str(link[1]) + "),"

    sql = sql[:-1] + ";"
    c.execute(sql)

    conn.commit()
    conn.close()


if __name__ == '__main__':
    main()
