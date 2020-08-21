import sqlite3


def main():
    conn = sqlite3.connect("../test.db")
    c = conn.cursor()

    c.execute("DELETE FROM record;")
    conn.commit()

    sql = "INSERT INTO record (hash_r, start) VALUES "

    lines = []

    with open("../links_mic.txt") as f:
        for line in f:
            lines.append(line.strip())

    lines = list(set(lines))

    links = []
    for line in lines:
        links.append(line.split(";"))

    for link in links:
        sql += "(" + str(link[0]) + "," + str(link[1]) + "),"

    sql = sql[:-1] + ";"
    c.execute(sql)
    conn.commit()

    c.execute("SELECT hashtable.id, COUNT(*) AS n "
              "FROM hashtable INNER JOIN record "
              "ON hashtable.hash = record.hash_r "
              "GROUP BY hashtable.time-record.start, id "
              "ORDER BY n DESC")

    rows = c.fetchall()

    for row in rows:
        print(row)


if __name__ == '__main__':
    main()
