CREATE PROCEDURE [dbo].[get_zone_page_def]
AS
SET NOCOUNT ON
	--SELECT @page_id = page_id, @page_name = page_name from zone_page_def;
	select * FROM zone_page_def;
RETURN 0
