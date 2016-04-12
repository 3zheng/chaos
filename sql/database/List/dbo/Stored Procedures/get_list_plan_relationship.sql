CREATE PROCEDURE [dbo].[get_list_plan_relationship]
AS
SET NOCOUNT ON
	--SELECT @plan_id = plan_id, @list_id = list_id from list_plan_relationship where show_state = 1 order by list_id
	select * FROM list_plan_relationship WHERE show_state = 1 ORDER BY show_order desc 
RETURN 0
