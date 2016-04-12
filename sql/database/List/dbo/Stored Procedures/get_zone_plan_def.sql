CREATE PROCEDURE [dbo].[get_zone_plan_def]
AS
SET NOCOUNT ON
	select * from zone_plan_def where show_state = 1
RETURN 0
