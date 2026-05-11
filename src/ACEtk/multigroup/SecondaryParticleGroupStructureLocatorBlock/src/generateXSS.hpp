static std::vector< double >
generateXSS( std::vector< unsigned int >&& locators ) {

  std::vector< double > xss;
  const auto nsec = locators.size();
  xss.reserve( nsec );
  xss.insert( xss.end(), locators.begin(), locators.end() );
  return xss;
}
