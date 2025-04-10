CREATE SEQUENCE gera_id
	start with 1
	increment by 2 
	minvalue 1
	maxvalue 100000
	cache 20
	NO cycle;

CREATE DOMAIN city AS VARCHAR(30)
	DEFAULT 'sem cidade'
	NOT NULL
	CONSTRAINT inicio_pal check(	
		value like 'S%'
		and value not like '...inas%'
	);

CREATE TABLE categorias(
	-- é uma chave primária e tem chave estrangeira pra ela
	idc int, 
	sigla char(3), 
	nusp int Unique,
	--coloca como chave primária da tabela
	Primary key (idc)
);

CREATE TABLE Aluno(
	nome Varchar(30) NOT NULL,
	cidade city,
	idx int Primary key, -- restrição do atributo 
	preco decimal(100, 2) check(preco >= 0),
	qtd int default 0, 
	Foreign key(idx) references categorias(idc)
);
