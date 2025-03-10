// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/Table.hpp"

// namespace aliases
namespace python = pybind11;

void wrapHeader( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ACEtk::Table::Header;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Header",
    "The header in an ACE table"
  );

  // wrap the component
  component
  .def(

    python::init< const std::string&, double, double,
                  const std::string&, const std::string&,
                  const std::string& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "temperature" ),
    python::arg( "date" ), python::arg( "title" ), python::arg( "material" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the header\n"
    "    zaid           the zaid (max 10 characters)\n"
    "    awr            the atomic weight ratio (to the neutron mass)\n"
    "    temperature    the temperature in MeV\n"
    "    date           the date (max 10 characters)\n"
    "    title          the title (max 70 characters)\n"
    "    material       the material (max 10 characters)"
  )
  .def_property_readonly(

    "VERS",
    &Component::VERS,
    "The header version"
  )
  .def_property_readonly(

    "version",
    &Component::version,
    "The header version"
  )
  .def_property_readonly(

    "zaid",
    &Component::ZAID,
    "The full ZAID or SZAID of the table"
  )
  .def_property_readonly(

    "AWR",
    &Component::AWR,
    "The atomic weight ratio (with respect to the neutron mass)"
  )
  .def_property_readonly(

    "atomic_weight_ratio",
    &Component::atomicWeightRatio,
    "The atomic weight ratio (with respect to the neutron mass)"
  )
  .def_property_readonly(

    "TEMP",
    &Component::TEMP,
    "The temperature of the table"
  )
  .def_property_readonly(

    "temperature",
    &Component::temperature,
    "The temperature of the table"
  )
  .def_property_readonly(

    "date",
    &Component::date,
    "The date"
  )
  .def_property_readonly(

    "title",
    &Component::title,
    "The title"
  )
  .def_property_readonly(

    "material",
    &Component::material,
    "The material"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string ) -> Component {

      njoy::ACEtk::State< decltype(string.begin()) > state{ 1, string.begin(), string.end() };
      return Component( state );
    },
    python::arg( "string" ),
    "Read the ACE header from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "header\n\n"
    "Arguments:\n"
    "    string    the string representing the ACE header"
  )
  .def(

    "to_string",
    [] ( const Component& self ) {

      std::ostringstream out;
      self.print( out );
      return out.str();
    },
    "Return the string representation of the ACE table"
  );
}
