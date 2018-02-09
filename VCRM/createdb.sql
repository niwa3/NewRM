--
-- PostgreSQL database dump
--

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
-- Name: set_update_time(); Type: FUNCTION; Schema: public; Owner: testuser
--

CREATE FUNCTION set_update_time() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
  begin
  new.updated_at := 'now';
  return new;
  end;
$$;


ALTER FUNCTION public.set_update_time() OWNER TO testuser;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: customer_info; Type: TABLE; Schema: public; Owner: testuser; Tablespace: 
--

CREATE TABLE customer_info (
    id integer NOT NULL,
    created_at timestamp without time zone DEFAULT now() NOT NULL,
    updated_at timestamp without time zone DEFAULT now() NOT NULL,
    l_id integer NOT NULL,
    last_name character varying(64) NOT NULL,
    first_name character varying(64) NOT NULL,
    birthday timestamp without time zone NOT NULL,
    e_mail_addr character varying(64) NOT NULL,
    phone_num character varying(255)
);


ALTER TABLE public.customer_info OWNER TO testuser;

--
-- Name: customer_info_id_seq; Type: SEQUENCE; Schema: public; Owner: testuser
--

CREATE SEQUENCE customer_info_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.customer_info_id_seq OWNER TO testuser;

--
-- Name: customer_info_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: testuser
--

ALTER SEQUENCE customer_info_id_seq OWNED BY customer_info.id;


--
-- Name: device_info; Type: TABLE; Schema: public; Owner: testuser; Tablespace: 
--

CREATE TABLE device_info (
    id integer NOT NULL,
    created_at timestamp without time zone DEFAULT now() NOT NULL,
    updated_at timestamp without time zone DEFAULT now() NOT NULL,
    c_id integer NOT NULL,
    device_name character varying(64) NOT NULL,
    default_privacy_standard integer NOT NULL,
    device_type integer NOT NULL,
    data_type integer NOT NULL,
    "interval" integer NOT NULL,
    location character varying(255) NOT NULL
);


ALTER TABLE public.device_info OWNER TO testuser;

--
-- Name: device_info_id_seq; Type: SEQUENCE; Schema: public; Owner: testuser
--

CREATE SEQUENCE device_info_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.device_info_id_seq OWNER TO testuser;

--
-- Name: device_info_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: testuser
--

ALTER SEQUENCE device_info_id_seq OWNED BY device_info.id;


--
-- Name: login_info; Type: TABLE; Schema: public; Owner: testuser; Tablespace: 
--

CREATE TABLE login_info (
    id integer NOT NULL,
    created_at timestamp without time zone DEFAULT now() NOT NULL,
    updated_at timestamp without time zone DEFAULT now() NOT NULL,
    login character varying(64) NOT NULL,
    passwd character varying(64) NOT NULL,
    salt character varying(64) NOT NULL,
    user_type integer NOT NULL
);


ALTER TABLE public.login_info OWNER TO testuser;

--
-- Name: login_info_id_seq; Type: SEQUENCE; Schema: public; Owner: testuser
--

CREATE SEQUENCE login_info_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.login_info_id_seq OWNER TO testuser;

--
-- Name: login_info_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: testuser
--

ALTER SEQUENCE login_info_id_seq OWNED BY login_info.id;

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
-- Name: service_info; Type: TABLE; Schema: public; Owner: testuser; Tablespace: 
--

CREATE TABLE service_info (
    id integer NOT NULL,
    created_at timestamp without time zone DEFAULT now() NOT NULL,
    updated_at timestamp without time zone DEFAULT now() NOT NULL,
    v_id integer NOT NULL,
    service_name character varying(64) NOT NULL,
    required_privacy_standard integer NOT NULL,
    data_type integer NOT NULL,
    "interval" integer NOT NULL
);


ALTER TABLE public.service_info OWNER TO testuser;

--
-- Name: service_info_id_seq; Type: SEQUENCE; Schema: public; Owner: testuser
--

CREATE SEQUENCE service_info_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.service_info_id_seq OWNER TO testuser;

--
-- Name: service_info_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: testuser
--

ALTER SEQUENCE service_info_id_seq OWNED BY service_info.id;

--
-- Name: vender_info; Type: TABLE; Schema: public; Owner: testuser; Tablespace: 
--

CREATE TABLE vender_info (
    id integer NOT NULL,
    created_at timestamp without time zone DEFAULT now() NOT NULL,
    updated_at timestamp without time zone DEFAULT now() NOT NULL,
    l_id integer NOT NULL,
    name character varying(64) NOT NULL,
    phone_num character varying(255) NOT NULL,
    e_mail_addr character varying(64) NOT NULL
);


ALTER TABLE public.vender_info OWNER TO testuser;

--
-- Name: vender_info_id_seq; Type: SEQUENCE; Schema: public; Owner: testuser
--

CREATE SEQUENCE vender_info_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.vender_info_id_seq OWNER TO testuser;

--
-- Name: vender_info_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: testuser
--

ALTER SEQUENCE vender_info_id_seq OWNED BY vender_info.id;


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY customer_info ALTER COLUMN id SET DEFAULT nextval('customer_info_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY device_info ALTER COLUMN id SET DEFAULT nextval('device_info_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY login_info ALTER COLUMN id SET DEFAULT nextval('login_info_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY relationship ALTER COLUMN id SET DEFAULT nextval('relationship_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY service_info ALTER COLUMN id SET DEFAULT nextval('service_info_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY vender_info ALTER COLUMN id SET DEFAULT nextval('vender_info_id_seq'::regclass);


--
-- Name: consumer_info_l_id_key; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY customer_info
    ADD CONSTRAINT consumer_info_l_id_key UNIQUE (l_id);


--
-- Name: consumer_info_pkey; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY customer_info
    ADD CONSTRAINT consumer_info_pkey PRIMARY KEY (id);


--
-- Name: device_info_device_name_key; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY device_info
    ADD CONSTRAINT device_info_device_name_key UNIQUE (device_name);


--
-- Name: device_info_pkey; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY device_info
    ADD CONSTRAINT device_info_pkey PRIMARY KEY (id);


--
-- Name: login_info_login_key; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY login_info
    ADD CONSTRAINT login_info_login_key UNIQUE (login);


--
-- Name: login_info_pkey; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY login_info
    ADD CONSTRAINT login_info_pkey PRIMARY KEY (id);


--
-- Name: relationship_pkey; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY relationship
    ADD CONSTRAINT relationship_pkey PRIMARY KEY (id);


--
-- Name: service_info_pkey; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY service_info
    ADD CONSTRAINT service_info_pkey PRIMARY KEY (id);


--
-- Name: service_info_service_name_key; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY service_info
    ADD CONSTRAINT service_info_service_name_key UNIQUE (service_name);


--
-- Name: vender_info_l_id_key; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY vender_info
    ADD CONSTRAINT vender_info_l_id_key UNIQUE (l_id);


--
-- Name: vender_info_pkey; Type: CONSTRAINT; Schema: public; Owner: testuser; Tablespace: 
--

ALTER TABLE ONLY vender_info
    ADD CONSTRAINT vender_info_pkey PRIMARY KEY (id);


--
-- Name: d_id_index; Type: INDEX; Schema: public; Owner: testuser; Tablespace: 
--

CREATE INDEX d_id_index ON relationship USING btree (d_id);


--
-- Name: s_id_index; Type: INDEX; Schema: public; Owner: testuser; Tablespace: 
--

CREATE INDEX s_id_index ON relationship USING btree (s_id);


--
-- Name: update_tri; Type: TRIGGER; Schema: public; Owner: testuser
--

CREATE TRIGGER update_tri BEFORE UPDATE ON customer_info FOR EACH ROW EXECUTE PROCEDURE set_update_time();


--
-- Name: update_tri; Type: TRIGGER; Schema: public; Owner: testuser
--

CREATE TRIGGER update_tri BEFORE UPDATE ON vender_info FOR EACH ROW EXECUTE PROCEDURE set_update_time();


--
-- Name: update_tri; Type: TRIGGER; Schema: public; Owner: testuser
--

CREATE TRIGGER update_tri BEFORE UPDATE ON device_info FOR EACH ROW EXECUTE PROCEDURE set_update_time();


--
-- Name: update_tri; Type: TRIGGER; Schema: public; Owner: testuser
--

CREATE TRIGGER update_tri BEFORE UPDATE ON service_info FOR EACH ROW EXECUTE PROCEDURE set_update_time();


--
-- Name: update_tri; Type: TRIGGER; Schema: public; Owner: testuser
--

CREATE TRIGGER update_tri BEFORE UPDATE ON relationship FOR EACH ROW EXECUTE PROCEDURE set_update_time();


--
-- Name: consumer_info_l_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY customer_info
    ADD CONSTRAINT consumer_info_l_id_fkey FOREIGN KEY (l_id) REFERENCES login_info(id);


--
-- Name: device_info_c_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY device_info
    ADD CONSTRAINT device_info_c_id_fkey FOREIGN KEY (c_id) REFERENCES customer_info(id);


--
-- Name: relationship_d_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY relationship
    ADD CONSTRAINT relationship_d_id_fkey FOREIGN KEY (d_id) REFERENCES device_info(id);


--
-- Name: relationship_device_name_fkey; Type: FK CONSTRAINT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY relationship
    ADD CONSTRAINT relationship_device_name_fkey FOREIGN KEY (device_name) REFERENCES device_info(device_name);


--
-- Name: relationship_s_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY relationship
    ADD CONSTRAINT relationship_s_id_fkey FOREIGN KEY (s_id) REFERENCES service_info(id);


--
-- Name: relationship_service_name_fkey; Type: FK CONSTRAINT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY relationship
    ADD CONSTRAINT relationship_service_name_fkey FOREIGN KEY (service_name) REFERENCES service_info(service_name);


--
-- Name: service_info_v_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY service_info
    ADD CONSTRAINT service_info_v_id_fkey FOREIGN KEY (v_id) REFERENCES vender_info(id);


--
-- Name: vender_info_l_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: testuser
--

ALTER TABLE ONLY vender_info
    ADD CONSTRAINT vender_info_l_id_fkey FOREIGN KEY (l_id) REFERENCES login_info(id);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

