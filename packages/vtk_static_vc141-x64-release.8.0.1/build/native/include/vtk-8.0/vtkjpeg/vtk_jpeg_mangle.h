#ifndef vtk_jpeg_mangle_h
#define vtk_jpeg_mangle_h

/*

This header file mangles all symbols exported from the jpeg library.
It is included in all files while building the jpeg library.  Due to
namespace pollution, no jpeg headers should be included in .h files in
VTK.

The following command was used to obtain the symbol list:

nm libvtkjpeg.a |grep " [TR] "

*/

#define jcopy_block_row vtk_jpeg_jcopy_block_row
#define jcopy_sample_rows vtk_jpeg_jcopy_sample_rows
#define jdiv_round_up vtk_jpeg_jdiv_round_up
#define jinit_1pass_quantizer vtk_jpeg_jinit_1pass_quantizer
#define jinit_2pass_quantizer vtk_jpeg_jinit_2pass_quantizer
#define jinit_c_coef_controller vtk_jpeg_jinit_c_coef_controller
#define jinit_c_main_controller vtk_jpeg_jinit_c_main_controller
#define jinit_c_master_control vtk_jpeg_jinit_c_master_control
#define jinit_c_prep_controller vtk_jpeg_jinit_c_prep_controller
#define jinit_color_converter vtk_jpeg_jinit_color_converter
#define jinit_color_deconverter vtk_jpeg_jinit_color_deconverter
#define jinit_compress_master vtk_jpeg_jinit_compress_master
#define jinit_d_coef_controller vtk_jpeg_jinit_d_coef_controller
#define jinit_d_main_controller vtk_jpeg_jinit_d_main_controller
#define jinit_d_post_controller vtk_jpeg_jinit_d_post_controller
#define jinit_downsampler vtk_jpeg_jinit_downsampler
#define jinit_forward_dct vtk_jpeg_jinit_forward_dct
#define jinit_huff_decoder vtk_jpeg_jinit_huff_decoder
#define jinit_huff_encoder vtk_jpeg_jinit_huff_encoder
#define jinit_input_controller vtk_jpeg_jinit_input_controller
#define jinit_inverse_dct vtk_jpeg_jinit_inverse_dct
#define jinit_marker_reader vtk_jpeg_jinit_marker_reader
#define jinit_marker_writer vtk_jpeg_jinit_marker_writer
#define jinit_master_decompress vtk_jpeg_jinit_master_decompress
#define jinit_memory_mgr vtk_jpeg_jinit_memory_mgr
#define jinit_merged_upsampler vtk_jpeg_jinit_merged_upsampler
#define jinit_phuff_decoder vtk_jpeg_jinit_phuff_decoder
#define jinit_phuff_encoder vtk_jpeg_jinit_phuff_encoder
#define jinit_upsampler vtk_jpeg_jinit_upsampler
#define jpeg_CreateCompress vtk_jpeg_CreateCompress
#define jpeg_CreateDecompress vtk_jpeg_CreateDecompress
#define jpeg_abort vtk_jpeg_abort
#define jpeg_abort_compress vtk_jpeg_abort_compress
#define jpeg_abort_decompress vtk_jpeg_abort_decompress
#define jpeg_add_quant_table vtk_jpeg_add_quant_table
#define jpeg_alloc_huff_table vtk_jpeg_alloc_huff_table
#define jpeg_alloc_quant_table vtk_jpeg_alloc_quant_table
#define jpeg_calc_output_dimensions vtk_jpeg_calc_output_dimensions
#define jpeg_consume_input vtk_jpeg_consume_input
#define jpeg_copy_critical_parameters vtk_jpeg_copy_critical_parameters
#define jpeg_default_colorspace vtk_jpeg_default_colorspace
#define jpeg_destroy vtk_jpeg_destroy
#define jpeg_destroy_compress vtk_jpeg_destroy_compress
#define jpeg_destroy_decompress vtk_jpeg_destroy_decompress
#define jpeg_fdct_float vtk_jpeg_fdct_float
#define jpeg_fdct_ifast vtk_jpeg_fdct_ifast
#define jpeg_fdct_islow vtk_jpeg_fdct_islow
#define jpeg_fill_bit_buffer vtk_jpeg_fill_bit_buffer
#define jpeg_finish_compress vtk_jpeg_finish_compress
#define jpeg_finish_decompress vtk_jpeg_finish_decompress
#define jpeg_finish_output vtk_jpeg_finish_output
#define jpeg_free_large vtk_jpeg_free_large
#define jpeg_free_small vtk_jpeg_free_small
#define jpeg_gen_optimal_table vtk_jpeg_gen_optimal_table
#define jpeg_get_large vtk_jpeg_get_large
#define jpeg_get_small vtk_jpeg_get_small
#define jpeg_has_multiple_scans vtk_jpeg_has_multiple_scans
#define jpeg_huff_decode vtk_jpeg_huff_decode
#define jpeg_idct_1x1 vtk_jpeg_idct_1x1
#define jpeg_idct_2x2 vtk_jpeg_idct_2x2
#define jpeg_idct_4x4 vtk_jpeg_idct_4x4
#define jpeg_idct_float vtk_jpeg_idct_float
#define jpeg_idct_ifast vtk_jpeg_idct_ifast
#define jpeg_idct_islow vtk_jpeg_idct_islow
#define jpeg_input_complete vtk_jpeg_input_complete
#define jpeg_make_c_derived_tbl vtk_jpeg_make_c_derived_tbl
#define jpeg_make_d_derived_tbl vtk_jpeg_make_d_derived_tbl
#define jpeg_mem_available vtk_jpeg_mem_available
#define jpeg_mem_init vtk_jpeg_mem_init
#define jpeg_mem_src vtk_jpeg_mem_src
#define jpeg_mem_term vtk_jpeg_mem_term
#define jpeg_natural_order vtk_jpeg_natural_order
#define jpeg_new_colormap vtk_jpeg_new_colormap
#define jpeg_open_backing_store vtk_jpeg_open_backing_store
#define jpeg_quality_scaling vtk_jpeg_quality_scaling
#define jpeg_read_coefficients vtk_jpeg_read_coefficients
#define jpeg_read_header vtk_jpeg_read_header
#define jpeg_read_raw_data vtk_jpeg_read_raw_data
#define jpeg_read_scanlines vtk_jpeg_read_scanlines
#define jpeg_resync_to_restart vtk_jpeg_resync_to_restart
#define jpeg_save_markers vtk_jpeg_save_markers
#define jpeg_set_colorspace vtk_jpeg_set_colorspace
#define jpeg_set_defaults vtk_jpeg_set_defaults
#define jpeg_set_linear_quality vtk_jpeg_set_linear_quality
#define jpeg_set_marker_processor vtk_jpeg_set_marker_processor
#define jpeg_set_quality vtk_jpeg_set_quality
#define jpeg_simple_progression vtk_jpeg_simple_progression
#define jpeg_start_compress vtk_jpeg_start_compress
#define jpeg_start_decompress vtk_jpeg_start_decompress
#define jpeg_start_output vtk_jpeg_start_output
#define jpeg_std_error vtk_jpeg_std_error
#define jpeg_std_message_table vtk_jpeg_std_message_table
#define jpeg_stdio_dest vtk_jpeg_stdio_dest
#define jpeg_stdio_src vtk_jpeg_stdio_src
#define jpeg_suppress_tables vtk_jpeg_suppress_tables
#define jpeg_write_coefficients vtk_jpeg_write_coefficients
#define jpeg_write_m_byte vtk_jpeg_write_m_byte
#define jpeg_write_m_header vtk_jpeg_write_m_header
#define jpeg_write_marker vtk_jpeg_write_marker
#define jpeg_write_raw_data vtk_jpeg_write_raw_data
#define jpeg_write_scanlines vtk_jpeg_write_scanlines
#define jpeg_write_tables vtk_jpeg_write_tables
#define jround_up vtk_jpeg_jround_up
#define jzero_far vtk_jpeg_jzero_far

#endif
