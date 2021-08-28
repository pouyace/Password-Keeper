
/*
	************************	CREATE TABLE	************************
CREATE TABLE app_users(
	username 	varchar(20) primary key,
    fName	 	varchar(20) not null,
	lName	 	varchar(20),
	pass_hint	varchar(30),
	user_pass	varchar(60)
);
	*/
/*	
	************************	CREATE TABLE	************************
CREATE TABLE app_data(
	item_id SERIAL primary key, 
	item_owner_user varchar(20) not null,
	item_username 	varchar(30) not null,
	item_website	varchar(30) not null,
	item_pass		varchar(60) not null,
	CONSTRAINT fk_customer
      FOREIGN KEY(item_owner_user) 
	  REFERENCES app_users(username)
		ON DELETE SET NULL
);
*/


/*
	************************	CREATE SEQUENCE	   ************************
CREATE SEQUENCE item_id_seq
START 10132
INCREMENT 1
MINVALUE 10132
OWNED BY app_data.item_id;
*/


/*
	************************	INSERT	************************
insert into app_users
values('theonepouya', 'Pouya', 'Mazji', 'Article+one+Name', 'theonepouya')
*/

/*
	************************	DELETE	************************
delete from app_users where username='theonepouya'
*/
/*
insert into app_data
values(nextval('item_id_seq'), 'theonepouya', 'thepouya.ce', 'gmail.com', 'pouya159@WSX')
	   */