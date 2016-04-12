
CREATE PROCEDURE [dbo].[get_zone_group_def]
AS
	SET NOCOUNT ON
--	SELECT @group_id = group_id, @group_name = group_name, @parent_page_id = parent_page_id, @group_type = group_type,
--		   @group_type_att_data = group_type_att_data, @show_order = show_order, @show_platform = show_platform
--	from zone_group_def where show_state = 1
	select * FROM zone_group_def where show_state = 1
RETURN 0
