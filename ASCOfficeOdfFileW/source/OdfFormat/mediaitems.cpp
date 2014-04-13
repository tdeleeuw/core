#include "precompiled_cpodf.h"
#include "mediaitems.h"
#include "odf_rels.h"

#include <regex.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/case_conv.hpp>

#include <cpdoccore/xml/utils.h>

#include "mediaitems_utils.h"
#include <cpdoccore/common/boost_filesystem_version.h>

namespace cpdoccore { 
namespace odf {


using boost::filesystem::wpath;

mediaitems::item::item(	std::wstring const & _oox_ref,
                       Type _type,
                       std::wstring const & _odf_ref
					   )
                       : oox_ref(_oox_ref),
                       type(_type),
                       odf_ref(_odf_ref)
{    

}


namespace fs = boost::filesystem;

void mediaitems::add_or_find(const std::wstring & oox_ref, Type type,  std::wstring & odf_ref)
{
	std::wstring output_sub_path;//
	std::wstring output_fileName;
	int number=0;
	
	if (type == typeImage)
	{
		output_sub_path = L"Pictures/";
		number= count_image+1;
	}
	else
	{
		output_sub_path = L"Media/";
		number= count_media+1;
	}

	
	output_fileName = utils::media::create_file_name(oox_ref, type, number);//guid???
	
	std::wstring input_path = oox_ref;
	boost::to_lower(input_path);
	std::wstring output_path ;

	std::wstring id;
    BOOST_FOREACH(item const & elm, items_)
    {
		if (elm.oox_ref == input_path)
		{
			output_path  = elm.odf_ref;
			break;
		}
	}
	if (output_path .length() < 1)
	{
		output_path = ( output_sub_path + output_fileName) ;
		if ( type == typeImage)
		{
			//fs::wpath file_name  = fs::wpath(inputPath);
			count_image++;
		}
		else
			count_media++;

		
		items_.push_back( item(input_path, type, xml::utils::replace_text_to_xml(output_path)) );
	}

	odf_ref = output_path;
}


}
}
