CREATE PROCEDURE [dbo].[get_group_list_relationship]
AS
SET NOCOUNT ON
	--SELECT @list_id = list_id, @group_id = group_id from group_list_relationship where show_state = 1 order by group_id
	select * FROM group_list_relationship WHERE show_state = 1 ORDER BY show_order desc 
RETURN 0
