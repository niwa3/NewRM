SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- Name: relationship; Type: TABLE; Schema: public; Owner: testuser; Tablespace: 
--

CREATE TABLE relationship (
    id integer NOT NULL,
    created_at timestamp without time zone DEFAULT now() NOT NULL,
    updated_at timestamp without time zone DEFAULT now() NOT NULL,
    d_id integer NOT NULL,
    device_name character varying(255) NOT NULL,
    s_id integer NOT NULL,
    service_name character varying(255) NOT NULL,
    anonymity_method integer NOT NULL,
    privacy_standard integer NOT NULL,
    "interval" integer NOT NULL,
    location character varying(255) NOT NULL
);


ALTER TABLE public.relationship OWNER TO testuser;

--
-- Name: relationship_id_seq; Type: SEQUENCE; Schema: public; Owner: testuser
--

CREATE SEQUENCE relationship_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.relationship_id_seq OWNER TO testuser;

--
-- Name: relationship_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: testuser
--

ALTER SEQUENCE relationship_id_seq OWNED BY relationship.id;

--
-- Name: id; Type: DEFAULT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY relationship ALTER COLUMN id SET DEFAULT nextval('relationship_id_seq'::regclass);

---
-- Name: relationship_pkey; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY relationship
    ADD CONSTRAINT relationship_pkey PRIMARY KEY (id);


--
-- Name: d_id_index; Type: INDEX; Schema: public; Owner: testuser; Tablespace: 
--

CREATE INDEX d_id_index ON relationship USING btree (d_id);


--
-- Name: s_id_index; Type: INDEX; Schema: public; Owner: testuser; Tablespace: 
--

CREATE INDEX s_id_index ON relationship USING btree (s_id);

--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;
