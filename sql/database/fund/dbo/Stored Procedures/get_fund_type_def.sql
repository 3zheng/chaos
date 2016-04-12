CREATE PROCEDURE [dbo].[get_fund_type_def]
AS
	SET NOCOUNT ON
--取所有财富id的定义
	select fund_id, fund_type, fund_name, att_fund_id, is_main_id from fund_type_def where is_outside_fund = 0
RETURN 0

