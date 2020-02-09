CREATE TABLE account (
    account_id INTEGER PRIMARY KEY,
    user_name VARCHAR,
    password VARCHAR,
    system_data_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE chip_card (
    chip_card_id INTEGER PRIMARY KEY,
    number VARCHAR(10),
    chip_card_door_id INTEGER,
    chip_card_profile_id INTEGER,
    employee_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE chip_card_door (
    chip_card_door_id INTEGER PRIMARY KEY,
    number VARCHAR(10),
    place_id INTEGER,
    department_id INTEGER,
    employee_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE chip_card_profile (
    chip_card_profile_id INTEGER PRIMARY KEY,
    number VARCHAR(10),
    chip_card_door_id INTEGER,
    employee_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE chip_card_profile_door (
    chip_card_profile_door_id INTEGER PRIMARY KEY,
    chip_card_profile_id INTEGER,
    chip_card_door_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE city_name (
    city_name_id INTEGER PRIMARY KEY,
    name VARCHAR,
    last_update TIMESTAMP
);

CREATE TABLE company (
    company_id INTEGER PRIMARY KEY,
    name VARCHAR,
    name2 VARCHAR,
    street VARCHAR,
    city VARCHAR,
    zip_code INTEGER,
    phone_number VARCHAR,
    fax_number VARCHAR,
    mobile_number VARCHAR,
    mail_address VARCHAR,
    active BOOLEAN,
    employee_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE computer (
    computer_id INTEGER PRIMARY KEY,
    device_name_id INTEGER,
    serial_number VARCHAR,
    service_tag VARCHAR,
    service_number VARCHAR,
    memory INTEGER,
    network VARCHAR,
    network_name VARCHAR,
    network_ip_address VARCHAR,
    active BOOLEAN,
    replace BOOLEAN,
    device_type_id INTEGER,
    employee_id INTEGER,
    place_id INTEGER,
    department_id INTEGER,
    manufacturer_id INTEGER,
    inventory_id INTEGER,
    processor_id INTEGER,
    os_id INTEGER,
    computer_software_id INTEGER,
    printer_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE computer_software (
    computer_software_id INTEGER PRIMARY KEY,
    computer_id INTEGER,
    software_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE department (
    department_id INTEGER PRIMARY KEY,
    name VARCHAR,
    priority INTEGER,
    printer_id INTEGER,
    fax_id INTEGER,
    last_update TIMESTAMP
 );

CREATE TABLE device_name (
    device_name_id INTEGER PRIMARY KEY,
    name VARCHAR,
    last_update TIMESTAMP
 );

CREATE TABLE device_type (
    device_type_id INTEGER PRIMARY KEY,
    name VARCHAR,
    last_update TIMESTAMP
);

CREATE TABLE document (
    document_id INTEGER PRIMARY KEY,
    name VARCHAR,
    document_data BLOB,
    last_update TIMESTAMP
);

CREATE TABLE employee_account (
    employee_account_id INTEGER PRIMARY KEY,
    employe_id INTEGER,
    account_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE employee (
    employee_id INTEGER PRIMARY KEY,
    employee_nr INTEGER,
    gender INTEGER,
    title_id INTEGER,
    first_name VARCHAR,
    last_name VARCHAR,
    birth_day DATE,
    address VARCHAR,
    zip_city_id INTEGER,
    home_phone VARCHAR,
    home_mobile VARCHAR,
    home_mail_address VARCHAR,
    business_mail_address VARCHAR,
    data_care BOOLEAN,
    active BOOLEAN,
    photo BLOB,
    notes VARCHAR,
    hire_date DATE,
    end_date DATE,
    department_id INTEGER,
    function_id INTEGER,
    computer_id INTEGER,
    printer_id INTEGER,
    phone_id INTEGER,
    mobile_id INTEGER,
    fax_id INTEGER,
    employee_account_id INTEGER,
    employee_document_id INTGER,
    chip_card_id INTEGER,
    last_update TIMESTAMP
 );

CREATE TABLE employee_document (
    employee_document_id INTEGER PRIMARY KEY,
    employe_id INTEGER,
    document_id INTEGER,
    last_update TIMESTAMP
 );

CREATE TABLE fax (
    fax_id INTEGER PRIMARY KEY,
    device_name_id INTEGER,
    serial_number VARCHAR,
    number VARCHAR,
    pin VARCHAR,
    active BOOLEAN,
    replace BOOLEAN,
    device_type_id INTEGER,
    employee_id INTEGER,
    place_id INTEGER,
    department_id INTEGER,
    manufacturer_id INTEGER,
    inventory_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE function (
    function_id INTEGER PRIMARY KEY,
    name VARCHAR,
    priority INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE inventory (
    inventory_id INTEGER PRIMARY KEY,
    number VARCHAR,
    text VARCHAR,
    active BOOLEAN,
    last_update TIMESTAMP
);

CREATE TABLE manufacturer (
    manufacturer_id INTEGER PRIMARY KEY,
    name VARCHAR,
    name2 VARCHAR,
    supporter VARCHAR,
    address VARCHAR,
    address2 VARCHAR,
    zip_city_id INTEGER,
    mail_address VARCHAR,
    phone_number VARCHAR,
    fax_number VARCHAR,
    hotline_number VARCHAR,
    last_update TIMESTAMP
);

CREATE TABLE mobile (
    mobile_id INTEGER PRIMARY KEY,
    device_name_id INTEGER,
    serial_number VARCHAR,
    number VARCHAR,
    pin VARCHAR,
    card_number VARCHAR,
    active BOOLEAN,
    replace BOOLEAN,
    device_type_id INTEGER,
    employe_id INTEGER,
    place_id INTEGER,
    department_id INTEGER,
    manufacturer_id INTEGER,
    inventory_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE os (
    os_id INTEGER PRIMARY KEY,
    name VARCHAR,
    version VARCHAR,
    revision VARCHAR,
    fix VARCHAR,
    last_update TIMESTAMP
);

CREATE TABLE phone (
    phone_id INTEGER PRIMARY KEY,
    device_name_id INTEGER,
    serial_number VARCHAR,
    number VARCHAR,
    pin VARCHAR,
    active BOOLEAN,
    replace BOOLEAN,
    device_type_id INTEGER,
    employe_id INTEGER,
    place_id INTEGER,
    department_id INTEGER,
    manufacturer_id INTEGER,
    inventory_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE place (
    place_id INTEGER PRIMARY KEY,
    name VARCHAR,
    room VARCHAR,
    desk VARCHAR,
    last_update TIMESTAMP
);

CREATE TABLE printer (
    printer_id INTEGER PRIMARY KEY,
    device_name_id INTEGER,
    serial_number VARCHAR,
    network VARCHAR,
    network_name VARCHAR,
    network_ip_address VARCHAR,
    active BOOLEAN,
    replace BOOLEAN,
    resources VARCHAR,
    paper_size_max VARCHAR,
    color BOOLEAN,
    device_type_id INTEGER,
    employe_id INTEGER,
    place_id INTEGER,
    department_id INTEGER,
    manufacturer_id INTEGER,
    inventory_id INTEGER,
    computer_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE processor (
    processor_id INTEGER PRIMARY KEY,
    name VARCHAR,
    clock_rate DECIMAL,
    cores INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE software (
    software_id INTEGER PRIMARY KEY,
    name VARCHAR,
    version VARCHAR,
    revision VARCHAR,
    fix VARCHAR,
    last_update TIMESTAMP
);

CREATE TABLE system_data (
    system_data_id INTEGER PRIMARY KEY,
    name VARCHAR,
    local BOOLEAN,
    company_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE title (
    title_id INTEGER PRIMARY KEY,
    name VARCHAR(50),
    from_date DATE,
    last_update TIMESTAMP
);

CREATE TABLE zip_city (
    zip_city_id INTEGER PRIMARY KEY,
    zip_code_id INTEGER,
    city_id INTEGER,
    last_update TIMESTAMP
);

CREATE TABLE zip_code (
    zip_code_id INTEGER PRIMARY KEY,
    code VARCHAR(10),
    last_update TIMESTAMP
);

CREATE TABLE database_version (
    database_version_id INTEGER PRIMARY KEY,
    version VARCHAR(10),
    revision VARCHAR (10),
    patch VARCHAR(10)
);

--First insertions

INSERT INTO database_version VALUES(1, "0", "90", "0");
