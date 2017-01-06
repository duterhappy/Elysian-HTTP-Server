/*
 * This file is part of Elysian Web Server
 *
 * Copyright (C) 2016,  Nikos Poulokefalos, npoulokefalos at gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include "elysian.h"

#include "fs_rom/fsdata.c"

uint8_t authentication_cb(elysian_t* server, char* url, char* username, char* password){

	ELYSIAN_LOG("[[ authentication_cb ]]");
	ELYSIAN_LOG("URL = %s, username = %s, password = %s", url, username, password);
	
	if(strcmp(url, "/fs_rom/basic_access_auth.html") == 0) {
		if((strcmp(username, "admin") == 0) && (strcmp(password, "admin") == 0)){
			return 1;
		} else {
			return 0; // wrong credentials
		}
	} 
	
	return 1; // all other pages authenticated by default
}

elysian_err_t controller_dynamic_page_html(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
	char attr_value[32];
    elysian_err_t err;

    ELYSIAN_LOG("[[ %s ]]", __func__);
    
	elysian_sprintf(attr_value, "%u", elysian_time_now());
	err = elysian_mvc_attribute_set(server, "attr_timestamp", attr_value);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	elysian_sprintf(attr_value, "%u", ELYSIAN_MAX_CLIENTS_NUM);
	err = elysian_mvc_attribute_set(server, "attr_ELYSIAN_MAX_CLIENTS_NUM", attr_value);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	elysian_sprintf(attr_value, "%u", ELYSIAN_MAX_MEMORY_USAGE_KB);
	err = elysian_mvc_attribute_set(server, "attr_ELYSIAN_MAX_MEMORY_USAGE_KB", attr_value);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	elysian_sprintf(attr_value, "%u", ELYSIAN_MAX_HTTP_BODY_SIZE_KB_RAM);
	err = elysian_mvc_attribute_set(server, "attr_ELYSIAN_MAX_HTTP_BODY_SIZE_KB_RAM", attr_value);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	elysian_sprintf(attr_value, "%u", ELYSIAN_MAX_HTTP_BODY_SIZE_KB_DISK);
	err = elysian_mvc_attribute_set(server, "attr_ELYSIAN_MAX_HTTP_BODY_SIZE_KB_DISK", attr_value);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    err = elysian_mvc_view_set(server, "/fs_rom/dynamic_page.html");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    return ELYSIAN_ERR_OK;
}

elysian_err_t controller_form_get(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
    char* str1;
	char* str2;
	char* str3;
	char* str4;
    uint8_t param_found;
    elysian_err_t err;
    char msg[256];
	
    ELYSIAN_LOG("[[ %s ]]", __func__);
    
    err = elysian_mvc_param_get_str(server, "param1", &str1, &param_found);
    if (err != ELYSIAN_ERR_OK){ 
        return err;
    }
	if (!param_found) {
		/* Parameter was not found */
	} else {
		/* Parameter found, data hold the data, datasize the size */
	}
	
    ELYSIAN_LOG("param1 = %s", str1);
    
    err = elysian_mvc_param_get_str(server, "param2", &str2, &param_found);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    ELYSIAN_LOG("param2 = %s", str2);
    
	err = elysian_mvc_param_get_str(server, "param3", &str3, &param_found);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    ELYSIAN_LOG("param3 = %s", str3);
	
	err = elysian_mvc_param_get_str(server, "param4", &str4, &param_found);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    ELYSIAN_LOG("param3 = %s", str3);
	
	elysian_sprintf(msg, "param1 value was '%s'<br>param2 value was '%s'<br>param3 value was '%s'<br>param4 value was '%s'<br>", str1, str2, str3, str4);
	ELYSIAN_LOG("MSG = %s", msg);
	
	err = elysian_mvc_attribute_set(server, "response_message", msg);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    err = elysian_mvc_view_set(server, "/fs_rom/form_get.html");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    
    return ELYSIAN_ERR_OK;
}

elysian_err_t controller_form_get_html(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
    elysian_err_t err;
	
    ELYSIAN_LOG("[[ %s ]]", __func__);

	err = elysian_mvc_attribute_set(server, "response_message", "");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    err = elysian_mvc_view_set(server, "/fs_rom/form_get.html");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    
    return ELYSIAN_ERR_OK;
}


elysian_err_t controller_form_post(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
    char* str1;
	char* str2;
	char* str3;
	char* str4;
    uint8_t param_found;
    elysian_err_t err;
    char msg[256];
	
    ELYSIAN_LOG("[[ %s ]]", __func__);
    
    err = elysian_mvc_param_get_str(server, "param1", &str1, &param_found);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    ELYSIAN_LOG("param1 = %s", str1);
    
    err = elysian_mvc_param_get_str(server, "param2", &str2, &param_found);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    ELYSIAN_LOG("param2 = %s", str2);
    
	err = elysian_mvc_param_get_str(server, "param3", &str3, &param_found);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    ELYSIAN_LOG("param3 = %s", str3);
	
	err = elysian_mvc_param_get_str(server, "param4", &str4, &param_found);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    ELYSIAN_LOG("param3 = %s", str3);
	
	elysian_sprintf(msg, "param1 value was '%s'<br>param2 value was '%s'<br>param3 value was '%s'<br>param4 value was '%s'<br>", str1, str2, str3, str4);
	ELYSIAN_LOG("MSG = %s", msg);
	
	err = elysian_mvc_attribute_set(server, "response_message", msg);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    err = elysian_mvc_view_set(server, "/fs_rom/form_post.html");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    
    return ELYSIAN_ERR_OK;
}

elysian_err_t controller_form_post_html(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
    elysian_err_t err;
	
    ELYSIAN_LOG("[[ %s ]]", __func__);

	err = elysian_mvc_attribute_set(server, "response_message", "");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    err = elysian_mvc_view_set(server, "/fs_rom/form_post.html");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }

    return ELYSIAN_ERR_OK;
}

elysian_err_t controller_file_upload(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
	uint32_t param_file1_size;
	char max_upload_size[16];
	char* param1_data;
    uint8_t param_found;
	elysian_req_param_t param_file1;
	uint32_t read_size;
    uint8_t file1_data[128];
	char data[256];
    elysian_err_t err;
	char* requested_url;
	char* param_file1_filename;
	
    ELYSIAN_LOG("[[ %s ]]", __func__);
    
	/*
	** Set the MVC view to be sent to the client
	** Check if this was called from a ROM or DISK page
	*/
	err = elysian_mvc_get_requested_url(server, &requested_url);
	if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	/*
	** Set the value to the attr_max_upload_size attribute
	*/
	if (strcmp(requested_url, "/fs_rom/file_upload_controller") == 0) {
		elysian_sprintf(max_upload_size, "%u", ELYSIAN_MAX_HTTP_BODY_SIZE_KB_RAM);
	} else {
		// requested URL was "file_upload_disk_controller"
		elysian_sprintf(max_upload_size, "%u", ELYSIAN_MAX_HTTP_BODY_SIZE_KB_DISK);
	}
	err = elysian_mvc_attribute_set(server, "attr_max_upload_size", max_upload_size);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	/*
	** Read the complete param1 parameter as string and just print it..
	*/
    err = elysian_mvc_param_get_str(server, "param1", &param1_data, &param_found);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    ELYSIAN_LOG("param1 = %s", param1_data);
    
	/*
	** Retrieve the file1 parameter
	*/
	err = elysian_mvc_param_get(server, "file1", &param_file1);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	/*
	** Read the first bytes of the file1 parameter
	*/
	err = elysian_mvc_param_read(server, &param_file1, 0, file1_data, sizeof(file1_data) - 1, &read_size);
	if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	file1_data[read_size] = '\0';
	
	/*
	** Set the value to the attr_uploaded_file_size attribute
	*/
	err = elysian_mvc_param_size(server, &param_file1, &param_file1_size);
	if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	err = elysian_mvc_param_filename(server, &param_file1, &param_file1_filename);
	if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	elysian_sprintf(data, "<b>The size of the uploaded file (%s) was %u bytes.</b><br>param1 value was '%s'. <br><br>", param_file1_filename, param_file1_size, param1_data);
	err = elysian_mvc_attribute_set(server, "attr_uploaded_file_size", data);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	/*
	** Set the value to the attr_uploaded_file_data attribute
	*/
	elysian_sprintf(data, "<b>The first %u bytes of the uploaded file were:</b><br>'%s'", read_size, file1_data);
	err = elysian_mvc_attribute_set(server, "attr_uploaded_file_data", (char*) data);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	if (strcmp(requested_url, "/fs_rom/file_upload_controller") == 0) {
		err = elysian_mvc_view_set(server, "/fs_rom/file_upload.html");
	} else {
		// requested URL was "file_upload_disk_controller"
		err = elysian_mvc_view_set(server, "/fs_ext/file_upload_disk.html");
	}

    return ELYSIAN_ERR_OK;
}

elysian_err_t controller_file_upload_html(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
	char* requested_url;
	char max_upload_size[32];
    elysian_err_t err;

    ELYSIAN_LOG("[[ %s ]]", __func__);
    
	/*
	** Set the MVC view to be sent to the client
	** Check if this was called from a ROM or DISK page
	*/
	err = elysian_mvc_get_requested_url(server, &requested_url);
	if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	/*
	** Set the value to the attr_max_upload_size attribute
	*/
	if (strcmp(requested_url, "/fs_rom/file_upload.html") == 0) {
		elysian_sprintf(max_upload_size, "%u", ELYSIAN_MAX_HTTP_BODY_SIZE_KB_RAM);
	} else {
		// requested URL was "file_upload_disk_controller"
		elysian_sprintf(max_upload_size, "%u", ELYSIAN_MAX_HTTP_BODY_SIZE_KB_DISK);
	}
	err = elysian_mvc_attribute_set(server, "attr_max_upload_size", max_upload_size);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }

	err = elysian_mvc_attribute_set(server, "attr_uploaded_file_size", "");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	err = elysian_mvc_attribute_set(server, "attr_uploaded_file_data", "");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	if (strcmp(requested_url, "/fs_rom/file_upload.html") == 0) {
		err = elysian_mvc_view_set(server, "/fs_rom/file_upload.html");
	} else {
		err = elysian_mvc_view_set(server, "/fs_ext/file_upload_disk.html");
	}
	
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    return ELYSIAN_ERR_OK;
}


elysian_err_t controller_http_request_exposure_html(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
    elysian_err_t err;

    ELYSIAN_LOG("[[ %s ]]", __func__);
    
	err = elysian_mvc_attribute_set(server, "attr_http_request_headers", "(Not yet submitted)");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }

	err = elysian_mvc_attribute_set(server, "attr_http_request_body", "(Not yet submitted)");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }

	err = elysian_mvc_view_set(server, "/fs_rom/http_request_exposure.html");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    return ELYSIAN_ERR_OK;
}

elysian_err_t controller_http_request_exposure(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
	uint8_t param_found;
	char* str1;
	char* str2;
    elysian_err_t err;

    ELYSIAN_LOG("[[ %s ]]", __func__);
    
	err = elysian_mvc_param_get_str(server, ELYSIAN_MVC_PARAM_HTTP_HEADERS, &str1, &param_found);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }

	err = elysian_mvc_param_get_str(server, ELYSIAN_MVC_PARAM_HTTP_BODY, &str2, &param_found);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	err = elysian_mvc_attribute_set(server, "attr_http_request_headers", str1);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }

	err = elysian_mvc_attribute_set(server, "attr_http_request_body", str2);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
	err = elysian_mvc_view_set(server, "/fs_rom/http_request_exposure.html");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    return ELYSIAN_ERR_OK;
}



elysian_err_t controller_redirected_page1_html(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
	char* str1;
	uint8_t param_found;
    elysian_err_t err;

    ELYSIAN_LOG("[[ %s ]]", __func__);
    
	err = elysian_mvc_param_get_str(server, "redirection_message", &str1, &param_found);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
    ELYSIAN_LOG("param1 = %s", str1);
	
	err = elysian_mvc_attribute_set(server, "redirection_message", str1);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    err = elysian_mvc_view_set(server, "/fs_rom/redirected_page1.html");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    return ELYSIAN_ERR_OK;
}

elysian_err_t controller_redirected_page0_html(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
    elysian_err_t err;

    ELYSIAN_LOG("[[ %s ]]", __func__);
    
	err = elysian_mvc_redirect(server, "/fs_rom/redirected_page1.html?redirection_message=this+is+a+custom+redirection+message");
	if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    return ELYSIAN_ERR_OK;
}

void controller_ajax_example_served(elysian_t* server, void* ptr) {
	char* ajax_file_name = (char*) ptr;
	
    ELYSIAN_LOG("[[ %s ]]", __func__);
	
	ELYSIAN_LOG("Removing temporary file '%s'..", ajax_file_name);
	elysian_fs_fremove(server, ajax_file_name);
	elysian_mem_free(server, ajax_file_name);
}

elysian_err_t controller_ajax(elysian_t* server){
	elysian_file_t ajax_file;
	uint32_t actual_write_sz;
	char* ajax_file_name;
	static uint32_t ajax_file_id = 0;
	char * ajax_file_contents = "<%=ajax_attr%>";
	char buffer[128];
	//elysian_client_t* client = elysian_current_client(server);
    elysian_err_t err;

    ELYSIAN_LOG("[[ %s ]]", __func__);
    
	ajax_file_name = elysian_mem_malloc(server, 64, ELYSIAN_MEM_MALLOC_PRIO_NORMAL);
	if(!ajax_file_name) {
		return ELYSIAN_ERR_POLL;
	}
	
	elysian_fs_finit(server, &ajax_file);
	elysian_sprintf(ajax_file_name, "%s%u%s", "/fs_ram/ajax_file_", ajax_file_id++, ".text");
	err = elysian_fs_fopen(server, ajax_file_name, ELYSIAN_FILE_MODE_WRITE, &ajax_file);
	if(err != ELYSIAN_ERR_OK){ 
		elysian_mem_free(server, ajax_file_name);
		return err;
	}
	err = elysian_fs_fwrite(server, &ajax_file, (uint8_t*)ajax_file_contents, strlen(ajax_file_contents), &actual_write_sz);
	if(err != ELYSIAN_ERR_OK){
		elysian_fs_fclose(server, &ajax_file);
		elysian_fs_fremove(server, ajax_file_name);
		elysian_mem_free(server, ajax_file_name);
        return err;
    }
	elysian_fs_fclose(server, &ajax_file);

	//elysian_sprintf(buffer, "[Timestamp %u] RAM usage is <b>%u</b> bytes.", elysian_time_now(), elysian_mem_usage());
	elysian_sprintf(buffer, "%u,%u", elysian_mem_usage(), ELYSIAN_MAX_MEMORY_USAGE_KB * 1024);
	err = elysian_mvc_attribute_set(server, "ajax_attr", buffer);
    if(err != ELYSIAN_ERR_OK){ 
		elysian_fs_fremove(server, ajax_file_name);
		elysian_mem_free(server, ajax_file_name);
        return err;
    }
	
	err = elysian_mvc_view_set(server, ajax_file_name);
    if(err != ELYSIAN_ERR_OK){ 
		elysian_fs_fremove(server, ajax_file_name);
		elysian_mem_free(server, ajax_file_name);
        return err;
    }
	
	elysian_mvc_set_reqserved_cb(server, controller_ajax_example_served, ajax_file_name);
	return ELYSIAN_ERR_OK;
}


elysian_err_t controller_file_download_html(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
	char attr_value[32];
    elysian_err_t err;

    ELYSIAN_LOG("[[ %s ]]", __func__);
    
	elysian_sprintf(attr_value, "%u", elysian_time_now());
	err = elysian_mvc_attribute_set(server, "attr_huge_file_path", ELYSIAN_FS_HUGE_FILE_VRT_ROOT "" ELYSIAN_FS_HUGE_FILE_NAME);
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    err = elysian_mvc_view_set(server, "/fs_rom/file_download.html");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    return ELYSIAN_ERR_OK;
}

elysian_err_t controller_dynamic_page_disk_html(elysian_t* server){
	//elysian_client_t* client = elysian_current_client(server);
	elysian_file_t disk_file;
	uint32_t file_size;
	char attr_value[64];
    elysian_err_t err;

    ELYSIAN_LOG("[[ %s ]]", __func__);
    
	elysian_fs_finit(server, &disk_file);
	err = elysian_fs_fopen(server, "/fs_ext/img1.jpg", ELYSIAN_FILE_MODE_READ, &disk_file);
	if(err != ELYSIAN_ERR_OK){ 
		return err;
	}
	
	err = elysian_fs_fsize(server, &disk_file, &file_size);
	if(err != ELYSIAN_ERR_OK){
		elysian_fs_fclose(server, &disk_file);
        return err;
    }
	
	elysian_fs_fclose(server, &disk_file);
	
	elysian_sprintf(attr_value, "<b>%u</b>", file_size);
	err = elysian_mvc_attribute_set(server, "attr_file_size", attr_value);
    if(err != ELYSIAN_ERR_OK){
        return err;
    }
	
    err = elysian_mvc_view_set(server, "/fs_ext/dynamic_page_disk.html");
    if(err != ELYSIAN_ERR_OK){ 
        return err;
    }
	
    return ELYSIAN_ERR_OK;
}


int main(){
	uint8_t stop = 0;
    elysian_t* server;
    
	ELYSIAN_LOG("Starting web server. SERVER %u, CLIENT %u, RESOURCE %u, TOTAL %u", (unsigned int) sizeof(elysian_t), (unsigned int) sizeof(elysian_client_t), (unsigned int) sizeof(elysian_resource_t), (unsigned int) (sizeof(elysian_t) + sizeof(elysian_client_t) + sizeof(elysian_resource_t)));
	
    server = elysian_new();
    
	/*
	** Controllers for files stored in ROM
	*/
	elysian_mvc_controller_add(server, "/fs_rom/dynamic_page.html", 
											controller_dynamic_page_html, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET);
	
	elysian_mvc_controller_add(server, "/fs_rom/form_get.html", 
											controller_form_get_html, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET);
	elysian_mvc_controller_add(server, "/fs_rom/form_get_controller", 
											controller_form_get, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET);
	
	elysian_mvc_controller_add(server, "/fs_rom/form_post.html", 
											controller_form_post_html, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET);
	elysian_mvc_controller_add(server, "/fs_rom/form_post_controller", 
											controller_form_post, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_POST);
	
	elysian_mvc_controller_add(server, "/fs_rom/file_upload.html", 
											controller_file_upload_html, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET);
	elysian_mvc_controller_add(server, "/fs_rom/file_upload_controller", 
											controller_file_upload, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_POST | ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_PUT);
	
	elysian_mvc_controller_add(server, "/fs_rom/http_request_exposure.html", 
							   controller_http_request_exposure_html, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET);
	elysian_mvc_controller_add(server, "/fs_rom/http_request_exposure_controller", 
							   controller_http_request_exposure, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET | ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_POST | ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_PUT);
	
	elysian_mvc_controller_add(server, "/fs_rom/redirected_page0.html", 
											controller_redirected_page0_html, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET | ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_POST);
	elysian_mvc_controller_add(server, "/fs_rom/redirected_page1.html", 
											controller_redirected_page1_html, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET);
	
	elysian_mvc_controller_add(server, "/fs_rom/ajax_controller", 
											controller_ajax, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET);
	
	elysian_mvc_controller_add(server, "/fs_rom/file_download.html", 
											controller_file_download_html, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET);
	
	/*
	** Controllers for files stored in external memory
	*/
	elysian_mvc_controller_add(server, "/fs_ext/dynamic_page_disk.html", 
											controller_dynamic_page_disk_html, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET);
	
	// Hits the same controller with the ROM alternative
	elysian_mvc_controller_add(server, "/fs_ext/file_upload_disk.html", 
											controller_file_upload_html, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_GET);
	elysian_mvc_controller_add(server, "/fs_ext/file_upload_disk_controller", 
											controller_file_upload, ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_POST | ELYSIAN_MVC_CONTROLLER_FLAG_HTTP_PUT | ELYSIAN_MVC_CONTROLLER_FLAG_USE_EXT_FS);

	elysian_rom_fs(server, rom_fs, sizeof(rom_fs) / sizeof(elysian_file_rom_t));
				   
    elysian_start(server, 9000, authentication_cb);
    
    while(!stop){
        elysian_poll(server, 4000);
    }
    
	elysian_stop(server);
	
    return 0;
}