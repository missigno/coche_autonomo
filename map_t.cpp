#include "map_t.h"

map_t::map_t(void):
  cells_(nullptr),
  n_(0),
  m_(0)
  {}

map_t::map_t(const cell_t n, const cell_t m):
  cells_(nullptr),
  n_(n),
  m_(m)
  {
    if(n_==0||m_==0)
    {
      std::cerr<<"Error: al mapa le falta alguna de las dimensiones."<<std::endl;
      exit(EXIT_FAILURE);
    }
    create_map();
  }

map_t::~map_t(void)
{
  destroy_map();
}

void map_t::read_file(std::string file_name)
{
  std::ifstream textfile;
  textfile.open(file_name);
  if(textfile.is_open())
  {
    std::clog<<"Fichero abierto satisfactoriamente."<<std::endl;
    my_size_t n,m;
    textfile>>n>>m;
    resize(n,m);
    const my_size_t size=n_*m_;
    for(my_size_t i=0; i<size; i++)
    {
      textfile>>n;  //reutilizamos la n para leer cada elemento
      cells_[i]=n;
    }
  }
  else
  {
    std::cerr<<"Error: no se ha podido abrir el fichero."<<std::endl;
    exit(EXIT_FAILURE);
  }
}


void map_t::write_file(std::string file_name)
{
  std::ofstream textfile;
  textfile.open(file_name);
  textfile<<n_<<" "<<m_<<std::endl;
  for(my_size_t i=1; i<=n_; i++)
  {
    textfile<<get(i,1);
    for(my_size_t j=2; j<=m_; j++)
      textfile<<" "<<get(i,j);
    textfile<<std::endl;
  }
  textfile.close();
}

void map_t::resize(const my_size_t n, const my_size_t m)
{
  destroy_map();
  n_=n;
  m_=m;
  create_map();
}

void map_t::create_map(void)
{
  const my_size_t size_=n_*m_;
  cells_=new cell_t[n_*m_];
  for(my_size_t i=0; i<size_; i++)
    cells_[i]=CeldaLibre; //reseteamos todas las celdas del mapa
  for(my_size_t j=1; j<=m_; j++)
    set(1,j,CeldaObstaculo);
  for(my_size_t i=2; i<n_; ++i)
  {
    set(i,1,CeldaObstaculo);
    set(i,m_,CeldaObstaculo);
    //et_set(i,1)=CeldaObstaculo;
    //(i,m_)=CeldaObstaculo;
  }
  for(my_size_t j=1; j<=m_; j++)
    set(n_,j,CeldaObstaculo);
    //(n_,j)=CeldaObstaculo;
    //for(my_size_t j=1; j<=penultimo; ++j)
      //(i,j)=CeldaObstaculo;

}

void map_t::destroy_map(void)
{
  if(cells_==nullptr)
    delete [] cells_;
  n_=m_=0;
}

my_size_t map_t::get_n(void) const
{
  return(n_);
}

my_size_t map_t::get_m(void) const
{
  return(m_);
}

cell_t map_t::get(const my_size_t i, const my_size_t j) const
{
  return(cells_[pos(i,j)]);
}

void map_t::set(const my_size_t i, const my_size_t j, const cell_t &x)
{
  cells_[pos(i,j)]=x;
}

cell_t& map_t::get_set(const my_size_t i, const my_size_t j)
{
  return(cells_[pos(i,j)]);
}

cell_t map_t::operator()(const my_size_t i, const my_size_t j) const
{
  return(get(i,j));
}

cell_t& map_t::operator()(const my_size_t i, const my_size_t j)
{
  return(get_set(i,j));
}

bool map_t::visitable(const my_size_t i, const my_size_t j) const
{
  if(i<1||j<1||i>n_||j>m_)
    return(0);
  return(get(i,j)!=CeldaObstaculo);
}


void map_t::visitar(const my_size_t i, const my_size_t j)
{
  switch(get(i,j))
  {
    case CeldaInicial:
    case CeldaFinal:
    case CeldaParadaVisitada:
    case CeldaLibreVisitada:
      break;
    case CeldaLibre:
      set(i,j,CeldaLibreVisitada);
      break;
    case CeldaParada:
      set(i,j,CeldaParadaVisitada);
      break;
    case CeldaObstaculo:
      std::cerr<<"Error, se esta visitando una celda obstáculo."<<std::endl;
      exit(EXIT_FAILURE);
      break;
    default:
      std::cerr<<"No se puede visitar esa celda."<<std::endl;
      exit(EXIT_FAILURE);
      break;
  }
}

bool map_t::final(const my_size_t i, const my_size_t j) const
{
  return(get(i,j)==CeldaFinal);
}

my_size_t map_t::paradas_visitadas(void) const
{
  my_size_t cont=0;
  const my_size_t size_=n_*m_;
  for(my_size_t i=0; i<size_; i++)
    if(cells_[i]==CeldaParadaVisitada)
      ++cont;
  return(cont);
}

my_size_t map_t::paradas_no_visitadas(void) const
{
  my_size_t cont=0;
  const my_size_t size_=n_*m_;
  for(my_size_t i=0; i<size_; i++)
    if(cells_[i]==CeldaParada)
      ++cont;
  return(cont);
}

void map_t::get_pos_coche(my_size_t &x, my_size_t &y)
{
  for(my_size_t i=1; i<n_; i++)
    for(my_size_t j=1; j<m_; j++)
      if(get(i,j)==CeldaInicial)
      {
        x=j;
        y=i;
        return;
      }
}

void map_t::get_pos_end(my_size_t &x, my_size_t &y)
{
  for(my_size_t i=1; i<n_; i++)
    for(my_size_t j=1; j<m_; j++)
      if(get(i,j)==CeldaFinal)
      {
        x=j;
        y=i;
        return;
      }
}

void map_t::generar_aleatorio(const double porcentaje, const my_size_t n_paradas)
{
  const my_size_t total=n_*m_;
  const my_size_t obstaculos=((double)(total))*porcentaje;
  my_size_t cont=0;
  my_size_t aux;
  bool baux;
  time_t semilla=time(NULL);
  std::clog<<"La semilla utilizada es la: "<<semilla<<std::endl;
  srand(semilla);
  do
  {
    aux=(rand()*clock())%total;
    if(cells_[aux]==CeldaLibre)
    {
      cells_[aux]=CeldaObstaculo;
      ++cont;
    }
  }
  while(cont<obstaculos);
  cont=0;
  do
  {
    aux=rand()%total;
    if(cells_[aux]==CeldaLibre)
    {
      cells_[aux]=CeldaParada;
      ++cont;
    }
  }
  while(cont<n_paradas);

  do
  {
    aux=rand()%total;
    if(cells_[aux]==CeldaLibre)
    {
      cells_[aux]=CeldaParada;
      ++cont;
    }
  }
  while(cont<n_paradas);
  baux=1;
  do
  {
    aux=rand()%total;
    if(cells_[aux]==CeldaLibre)
    {
      cells_[aux]=CeldaInicial;
      baux=0;
    }
  }
  while(baux);
  baux=1;
  do
  {
    aux=rand()%total;
    if(cells_[aux]==CeldaLibre)
    {
      cells_[aux]=CeldaFinal;
      baux=0;
    }
  }
  while(baux);
}

my_size_t map_t::pos(const my_size_t i, const my_size_t j) const
{
  if(i<1||j<1||i>n_||j>m_)
  {
    std::cerr<<"ERROR en el acceso al mapa."<<std::endl;
    exit(EXIT_FAILURE);
    //return(0);
    //return(CeldaObstaculo);
  }
  return((i-1)*m_+j-1);
}
