CREATE SCHEMA IF NOT EXISTS works;
CREATE TABLE IF NOT EXISTS works.work (
    id          serial      not null primary key,
    title       text        not null default 'work title',
    created_at  timestamp   not null default current_timestamp,
    updated_at  timestamp   not null default current_timestamp,
    detail      text        default null,
    media_urls  text[5]     default null,
    github      text        default null,
    zip         text        default null
);
CREATE SCHEMA IF NOT EXISTS manage;
CREATE TABLE IF NOT EXISTS manage.login (
    pass        text        not null default 'b109f3bbbc244eb82441917ed06d618b9008dd09b3befd1b5e07394c706a8bb980b1d7785e5976ec049b46df5f1326af5a2ea6d103fd07c95385ffab0cacbc86'
);
INSERT INTO manage.login (pass) VALUES (DEFAULT);