void page_init()
{
  setPage(0);
}

void pageMoveNext()
{
  page += 1;
  setPage(page);
}

void pageMovePrevious()
{
  page -= 1;
  setPage(page);
}

void setPage(uint8 _p)
{
  page = _p;  

  if (page < 0)
    page = 0;

}


