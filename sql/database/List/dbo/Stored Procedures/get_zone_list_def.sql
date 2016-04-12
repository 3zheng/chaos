CREATE PROCEDURE [dbo].[get_zone_list_def]
AS
SET NOCOUNT ON
--取状态值为有效的所有表记录
	--SELECT @list_id = list_id, @list_name = list_name, @list_type = list_type, 
	--		@show_order = show_order, @show_platform = show_platform
	--from zone_list_def where show_state = 1

	select * FROM zone_list_def where show_state = 1;
RETURN 0
